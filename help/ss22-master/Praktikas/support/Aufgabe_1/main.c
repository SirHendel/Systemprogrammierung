#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <pthread.h>

#define WIEDERHOLUNG 10
void handler (int signo);
struct sigaction act, oldact;

int main(int argc, char **argv) {
  pid_t pid;
  int status;
  int i = 0;
	
  act.sa_handler = handler;
  sigemptyset(&act.sa_mask);
  act.sa_flags = 0;
        
  /*Fehlermeldungen für Signale                  */
  if (sigaction(SIGUSR1, &act, &oldact) < 0) {
    perror("installing sighandler");
    exit(1);
  }

  //Die Signalmenge erzeugen
  if (sigemptyset(&act.sa_mask) < 0) {
    perror("SigEmptySet : ");
    exit(EXIT_FAILURE);
  }

  //Der Signalmenge das User1-Signal anfügen
  if (sigaddset(&act.sa_mask,SIGUSR1) < 0) {
    perror("SigAddSet : ");
    exit(EXIT_FAILURE);
  }

  //Signalmaske für Programm setzen
  if (sigprocmask(SIG_UNBLOCK,&act.sa_mask,NULL) < 0) {
    perror("SigProcMask : ");
    exit(EXIT_FAILURE);
  }
	
  switch (pid = fork()) {
  case -1:
    printf("Fehler: fork()-Resultat %d.\n", pid);
    exit(1);
    break;

  case 0:
    printf("Kind: PID = %u - Eltern-PID = %u\n",
	   getpid(), getppid());
    kill(getppid(), SIGUSR1);
    pause();
    while(i != WIEDERHOLUNG) {
      printf("Kindprozess PID-Nr %u\n",getpid());
      i++;
      if (i == WIEDERHOLUNG)
	break;
      if (kill(getppid(),SIGUSR1) < 0) {
	perror("Kind wurde gekillt, weil: ");
	exit(EXIT_FAILURE);
      }
      if (i != WIEDERHOLUNG)
	pause();
    }
			
    printf("Kind: Beendet.\n");
    exit(0);
    break;

  default:
    sleep(1);
    while(i != WIEDERHOLUNG) {
      printf("Elternprozess PID-Nr %u\n",getpid());
      i++;
      if (kill(pid,SIGUSR1) < 0) {
	perror("Gekilltes Elternteil: ");
	exit(EXIT_FAILURE);
      }
      if (i != WIEDERHOLUNG)
	pause();
    }
    pid = wait(&status);
    printf("Eltern: Kind mit PID %u ", pid);
    if (WIFEXITED(status) != 0)
      printf("wurde mit Status %d beendet\n",WEXITSTATUS(status));
    else if (WIFEXITED(status)) {
      printf("Parent: Child exited, status=%d\n", WEXITSTATUS(status));
    } else if (WIFSIGNALED(status)) {
      printf("Parent: Child killed by signal %d\n", WTERMSIG(status));
    } else if (WIFSTOPPED(status)) {
      printf("Parent: Child stopped by signal %d\n", WSTOPSIG(status));
    } else if (WIFCONTINUED(status)) {
      printf("Parent: Child continued\n");
    }
    while (!WIFEXITED(status) && !WIFSIGNALED(status));
	
    exit(EXIT_SUCCESS);
    break;
  }
  return 0;
}


/* Signalhandler */
void handler(int signo)
{
		
}
