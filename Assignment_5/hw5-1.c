#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>


int main(int argc,char **argv)
{
    pid_t ppid,cpid;
    int cnt,wstatus;
    cnt=1; // counter
    ppid=getpid();  // parent id
    // fork first time
    cpid=fork();    // child id
    waitpid(cpid,&wstatus,WUNTRACED);   // wait for child to execute
    // if current execute is parent get the status(counter value) at previous state
    if(cpid){
        cnt=WEXITSTATUS(wstatus);
    }
    // fork second time
    cpid=fork();
    waitpid(cpid,&wstatus,WUNTRACED);
    if(cpid){
        cnt=WEXITSTATUS(wstatus);
    }
    // fork third time
    cpid=fork();
    waitpid(cpid,&wstatus,WUNTRACED);
    if(cpid){
        cnt=WEXITSTATUS(wstatus);
    }
    // fork forth time
    cpid=fork();
    waitpid(cpid,&wstatus,WUNTRACED);
    if(cpid){
        cnt=WEXITSTATUS(wstatus);
    }
    // output the process
    printf("current execute pid=%d cnt=%d\n",getpid(),cnt);
    if(ppid!=getpid()){ // if change to child execute counter+1
        cnt++;
        return cnt;
    }
    return 0;
}
