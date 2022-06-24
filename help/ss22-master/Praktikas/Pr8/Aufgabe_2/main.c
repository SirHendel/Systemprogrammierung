#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <errno.h>

int main(int argc, char **argv) {
  pid_t npid = 0;

  // Prozess forken, sprich einen neuen Kindprozess erzeugen
  if((npid = fork()) == -1) {
    perror("fork");
    exit(EXIT_FAILURE);
  }

  // Falls npid == 0, dann ist es der Kindprozess
  if(npid == 0) {
    printf("[Kindprozess] -> PID [%d] PPID [%d]\n", getpid(), getppid());
    for (int x = 0; x <= 1000000000; ++x) { }
    puts("[Kindprozess] -> ist beendet");
    exit(0);
  } else { // Ansonsten das ausfuehrende Programm
    printf("[Vaterprozess] -> PID [%d] Kindprozess-PID [%d]\n", getpid(), npid);
    int status = 0;
    int ret = 0;

    // Laufe so lange, bis Kindprozess beendet
    while(ret == 0){
      // 1 Sekunde pause
      sleep(1);

      // Aufruf von waitpid, um zu schauen ob der Kindprozess noch laeuft
      if((ret = waitpid(npid, &status, WNOHANG)) == -1) {
	perror("waitpid");
	exit(EXIT_FAILURE);
      } else if (ret == 0) { // bei ret == 0 laeuuft der Prozess beendet ist
	puts("[Vaterprozess] -> Kindprozess läuft noch");
      }
    }

    // Status Wert von dem Kindprozess
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

  return EXIT_SUCCESS;
}
