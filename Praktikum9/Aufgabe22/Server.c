#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
#include <ctype.h>
#include <fcntl.h>

//server sachen
#define SERVER 1L
typedef struct {
    long    msg_to;
    long    msg_fm;
    char    *pathWritingFile;
    int     wdh;
    mode_t  quellemode;
    char    buffer[BUFSIZ];
} MESSAGE;

int mid;
key_t key;
struct msqid_ds buf;
MESSAGE msg;

int main(int argc, char **argv) {

    key = ftok(".", 'z');

    if((mid = msgget(key, IPC_CREAT | 0660))<0){
        printf("Error Creating Message Queue\n");
        exit(-1);
    }

    if(msgrcv(mid, &msg, sizeof(msg.buffer), SERVER, 0)<0){
            perror("msgrcv");
            exit(-1);
    }  

    int retValue = 0;
    // Deklaration und Definition der benoetigten Pfade
    char *pathWritingFile = msg.pathWritingFile;
    // Deklaration der Filedeskriptoren
    int fd_WritingFile;

   
    //Receiving message from client, throws and error if input is invalid
   
    if(access(pathWritingFile, F_OK) == 0) { // Die Zieldatei existiert bereits
        // Ueberpruefe ob Nutzer Schreibrecht hat
        if(access(pathWritingFile, W_OK) != 0) {
            fprintf(stderr, "Fuer die Zieldatei besteht kein Schreibrecht.\n");
            exit(EXIT_FAILURE);
        }
        // Oeffnen der Zieldatei
        fd_WritingFile = open(pathWritingFile, O_WRONLY);
        // CHECK: Pruefen ob die Zieldatei ein Verzeichnis ist
        if (errno == EISDIR) { 
            fprintf(stderr, "Die Zieldatei ist ein Verzeichnis\n");
            exit(EXIT_FAILURE);
        } else if(fd_WritingFile == -1) { 
            // CHECK: Pruefe ob Fehler beim Oeffnen der Zieldatei
            perror("Fehler beim Oeffnen der Zieldatei");
            exit(EXIT_FAILURE);
        }
        /* Hier wird gefragt, ob die Datei ueberschriebenw werden soll. */
        char inp = ' ';
        do {
            printf("Wollen Sie die datei ueberschreiben? (y/n)\n");
            inp = getchar();
            if(inp == 'n')
                exit(EXIT_SUCCESS);
        
        while(getchar() != '\n') { }
        } while (inp != 'y');
    } else { // Die Zieldatei existiert noch nicht
        // Erstellen der Datei
        fd_WritingFile = creat("teext.txt", msg.quellemode);
        // CHECK: Pruefe ob es ein Problem beim Erstellen der Zieldatei gab
        if(fd_WritingFile == -1) {
            perror("Fehler beim Erstellen der Zieldatei");
            perror(msg.pathWritingFile);
            exit(EXIT_FAILURE);
        }
    }

    /* Schleife, die entsprechend der Anzahl der Bloecke die Datei
        Stueckweise kopiert */

    msg.wdh = 1;

    for(int kopieren = 0; kopieren < msg.wdh; ++kopieren) {
        //Receiving message from client, throws and error if input is invalid
        if(msgrcv(mid, &msg, sizeof(msg.buffer), SERVER, 0)<0){
            perror("msgrcv");
            exit(-1);
        }
        printf("message %s",msg.buffer);
        // Schreiben des eingelesen Puffers bis maximal des return Values
        if(write(fd_WritingFile, msg.buffer, retValue) == -1) {
            perror("Fehler beim Schreiben");
            exit(EXIT_FAILURE);
        }
    }

    if (close(fd_WritingFile) == -1) {
        perror("Fehler beim Schliessen der Zieldatei");
        exit(EXIT_FAILURE);
    }

    return EXIT_SUCCESS;
}