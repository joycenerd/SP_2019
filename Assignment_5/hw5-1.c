#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>


int main(int argc,char **argv)
{
    pid_t ppid,cpid;
    int cnt,wstatus;
    cnt=1;
    ppid=getpid();
    cpid=fork();
    waitpid(cpid,&wstatus,WUNTRACED);
    if(cpid){
        cnt=WEXITSTATUS(wstatus);
    }
    cpid=fork();
    waitpid(cpid,&wstatus,WUNTRACED);
    if(cpid){
        cnt=WEXITSTATUS(wstatus);
    }
    cpid=fork();
    waitpid(cpid,&wstatus,WUNTRACED);
    if(cpid){
        cnt=WEXITSTATUS(wstatus);
    }
    cpid=fork();
    waitpid(cpid,&wstatus,WUNTRACED);
    if(cpid){
        cnt=WEXITSTATUS(wstatus);
    }
    printf("current execute pid=%d cnt=%d\n",getpid(),cnt);
    if(ppid!=getpid()){
        cnt++;
        return cnt;
    }
    return 0;
}