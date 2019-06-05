#include <errno.h>
#include <setjmp.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/resource.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>
char *argVect[200];
char *cmd;

void printSigMask() {
  sigset_t oldsigset;
  sigprocmask(SIG_SETMASK, NULL, &oldsigset);
  for (int i = 0; i < SIGRTMAX; i++) {
    if (sigismember(&oldsigset, i) == 1) {
      printf("Signal "
             "%s"
             " is blocked\n",
             sys_siglist[i]);
    }
  }
}

double getCurTime() {
  struct timespec now;
  clock_gettime(CLOCK_MONOTONIC, &now);
  double sec = now.tv_sec;
  double nano_sec = now.tv_nsec;
  return sec + nano_sec * 10E-9;
}

int parseString(char *str, char **cmd) {
  int idx = 0;
  char *retPtr;
  retPtr = strtok(str, " \n");
  while (retPtr != NULL) {
    argVect[idx++] = retPtr;
    if (idx == 1)
      *cmd = retPtr;
    retPtr = strtok(NULL, " \n");
  }
  argVect[idx] = NULL;
  return idx;
}

void ungets_ctr_c() {
  ungetc('\n', stdin);
  ungetc('c', stdin);
  ungetc('^', stdin);
}

int hasChild;
pid_t childPid;
sigjmp_buf jmpbuf;

void ctr_c(int signum) {
  printf("\nctr-c: ");                         //////////////////
  printSigMask();                              //////////////////
  printf("\n end of the report of sigmask\n"); //////////////////
  if (hasChild) {
    kill(childPid, SIGINT);
    hasChild = 0;
  } else {
    if (argVect[0] == NULL) {
      ungets_ctr_c();
      siglongjmp(jmpbuf, 1);
    }
  }
}

int main(int argc, char **argv) {
  char *exeName;
  pid_t pid;
  char cmdLine[256];
  signal(SIGINT, ctr_c);
  char *env[] = {getenv("HOME"), "LOGNAME=home", (char *)0};
  while (1) {
    // sigsetjmp(jmpbuf,1);
    hasChild = 0;      //////////////////
    argVect[0] = NULL; //////////////////
    printSigMask();
    ; //////////////////
    printf("myShell > ");
    ; //////////////////
    sigsetjmp(jmpbuf, 1);
    ; //////////////////
    fgets(cmdLine, 256, stdin);
    printf("the return of gets is %s\n", cmdLine);
    ; //////////////////
    int idx = parseString(cmdLine, &exeName);
    if (strcmp(cmdLine, "^c") == 0) {
      ; //////////////////
      printf("\n");
      continue;
    }
    if ((pid = fork()) > 0) { // parent，也就是shell的部分
      int tmp;
      childPid = pid;
      hasChild = 1;
      wait(&tmp); //等待child執行結束
    } else {
      printf("child execute the command %s\n", cmdLine);
      ; //////////////////
      if (idx == 1) {
        if (execle("/bin/ls", argVect[0], (char *)0, env) == -1) {
          perror("myShell");
          exit(errno * -1);
        }
      }
      if (idx == 2) {
        if (execle("/bin/ls", argVect[0], argVect[1], (char *)0, env) == -1) {
          perror("myShell");
          exit(errno * -1);
        }
      }
      if (idx == 2) {
        if (execle("/bin/ls", argVect[0], argVect[1], argVect[2], (char *)0,
                   env) == -1) {
          perror("myShell");
          exit(errno * -1);
        }
      }
      if (idx == 3) {
        if (execle("/bin/ls", argVect[0], argVect[1], argVect[2], argVect[3],
                   (char *)0, env) == -1) {
          perror("myShell");
          exit(errno * -1);
        }
      }
    }
  }
}
