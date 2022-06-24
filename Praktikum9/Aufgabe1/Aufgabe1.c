#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>
#include <errno.h>


void  sig_handler_child(int signum){
    if(signum == SIGUSR1){
        printf("Signal von pid: %d \n",getpid());
    }
}


int main(int argc,char* argv[]){

    sigset_t set;
    int sig;
    int *sigptr = &sig;
    if(sigemptyset(&set)<0){
        perror("sigemptyset");
        return EXIT_FAILURE;
    }
    if(sigaddset(&set, SIGUSR1)<0){
        perror("ssigaddset");
        return EXIT_FAILURE;
    }
    if(sigprocmask( SIG_BLOCK, &set, NULL )<0){
        perror("sigprocmask");
        return EXIT_FAILURE;
    }

    if(signal(SIGUSR1,sig_handler_child) == SIG_ERR){
        perror("signal error");
        return EXIT_FAILURE;
    }
    pid_t npid;

    npid = fork();

    if (npid == -1){
        perror("fork failed");
        return EXIT_FAILURE;
    } 

    for(int n = 0;n<10;n++){
        if(npid != 0){
            if(sigwait(&set,sigptr)<0){
                perror("sigwaiterror");
                return EXIT_FAILURE;
            } // wartet
            printf("Elternprozess PID-Nr %d \n",getpid());
            if(kill(npid,SIGUSR1)<0){
                perror("kill error");
                return EXIT_FAILURE;
            } // wartet   
        }
        else if(npid == 0){
            if(kill(getppid(),SIGUSR1)<0){
                perror("kill error");
                return EXIT_FAILURE;
            } // wartet
            if(sigwait(&set,sigptr)<0){
                perror("sigwaiterror");
                return EXIT_FAILURE;
            } // wartet
            printf("Kindprozess PID-Nr %d \n",getpid());
        }
    }
    return EXIT_SUCCESS;
}