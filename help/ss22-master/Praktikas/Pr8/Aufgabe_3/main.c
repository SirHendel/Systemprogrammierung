#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <assert.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>

int main(int argc, char **argv) {
  assert(argc >= 2); // Pruefe ob genuegend Argumente uebergeben sind
  pid_t npid = 0;

  // Prozess splitten, damit Kindprozess das externe Programm ausfuehrt
  // und der ausfuehrende Prozess die "Kontrolle" hat
  if((npid = fork()) == -1) {
    perror("fork");
    exit(EXIT_FAILURE);
  }

  // Speicher reservieren
  char **args = malloc(argc*sizeof(char *));
  assert(args != NULL);
  
  if(npid == 0) {
    sleep(0.25);
    printf("[Kindprozess] -> PID [%d] PPID [%d]\n", getpid(), getppid());

    // Befehl + Argumente in das neue Array schreiben
    for(int x = 1; x < argc; ++x) {
      args[x - 1] = argv[x];
    }
    args[argc - 1] = NULL;

    // Befehl + Argumente ausgeben
    printf("[Kindprozess] -> Starte Befehl: ");
    for(int x = 0; args[x] != NULL; ++x)
      printf("%s ", args[x]);
    printf("\n");

    printf(">>>>>>>>\n");
    // Befehl ausfuehren
    if ((execvp(args[0], args)) == -1) {
      perror("execvp");
      exit(EXIT_FAILURE);
    }
    printf("Das Programm wurde nicht richtig aufgerufen.\n");

  } else {
    printf("[Vaterprozess] -> PID [%d] Kindprozess-PID [%d]\n", getpid(), npid);

    int status = 0;
    int ret = 0;
    // Schleife, die so lange laeuft, bis der Kindprozess beendet ist
    while(ret == 0) {
      sleep(0.25);
      // Pruefen ob das Programm noch laeuuft
      if((ret = waitpid(npid, &status, WNOHANG)) == -1) {
	perror("waitpid");
	exit(EXIT_FAILURE);
      }
    }

    printf("<<<<<<<<\n");
    // Status des aufrufenden Programms interpretieren
    if (WIFEXITED(status)) {
      printf("[Vaterprozess] -> Kindprozess normal beendet mit [%d]\n",
	     WEXITSTATUS(status));
    } else if (WIFSIGNALED(status)) {
      printf("[Vaterprozess] -> Kindprozess beendet mit Signal [%d]\n",
	     WTERMSIG(status));
    } else if (WIFSTOPPED(status)) {
      printf("[Vaterprozess] -> Kindprozess gestoppt mit Signal [%d]\n",
	     WSTOPSIG(status));
    } else if (WIFCONTINUED(status)) {
      printf("[Vaterprozess] -> Kindprozess laeuft wieder weiter\n");
    }
  }

  // Speicher wieder freigeben
  free(args);
  args=NULL;

  return EXIT_SUCCESS;
}
