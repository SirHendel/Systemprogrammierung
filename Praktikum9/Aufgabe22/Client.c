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
    char    buffer[BUFSIZ];
    char    *pathWritingFile;
    int     wdh; 
    mode_t quellemode; 
} MESSAGE;

int mid;
key_t key;
struct msqid_ds buf;
MESSAGE msg;

int main(int argc, char **argv) {
    // CHECK: Pruefe ob Argumentenzahl passt
    if(argc != 3) {
        fprintf(stderr, "Die Parameteranzahl stimmt nicht.\n"
            "Bitte rufe das Program wie folgt auf:\n"
            "client [QUELLDATEI] [ZIELDATEI]\n");
        exit(EXIT_FAILURE);
    }

    // Deklaration und Definition der benoetigten Pfade
    char *pathReadingFile = argv[1];
    msg.pathWritingFile = argv[2];
    
   

    // Informationen ueber die Quelldatei
    struct stat bufReadingFile;

    // Deklaration der Filedeskriptoren
    int fd_ReadingFile;

    //Aquiring Message Queue ID
    key = ftok(".", 'z');
    mid = msgget(key, 0);

    msg.msg_to = SERVER;
    msg.msg_fm = (long)getpid(); 
    
   
    // CHECK: Pruefe ob Quelldatei existiert
    if(access(pathReadingFile, F_OK) == -1) {
        fprintf(stderr, "Die Quelldatei existiert nicht.\n");
        exit(EXIT_FAILURE);
    }
    // CHECK: Pruefe ob Leserecht vorhanden ist fuer die Quelldatei
    if(access(pathReadingFile, R_OK) == -1) {
        fprintf(stderr, "Die Quelldatei ist nicht lesbar\n");
        exit(EXIT_FAILURE);
    } 

    // Quelldatei oeffnen
    fd_ReadingFile = open(pathReadingFile, O_RDONLY);
    msg.quellemode = bufReadingFile.st_mode;
    // Hole informationen ueber die Quelldatei
    if(fstat(fd_ReadingFile, &bufReadingFile) == -1) {
        perror("Fehler beim Aufruf von fstat");
        exit(EXIT_FAILURE);
    }
    
    // Puffer entsprechend der optimalen Puffergroesse ermitteln.
    const blksize_t bufSize = bufReadingFile.st_blksize;
    msg.wdh = (int)bufReadingFile.st_blocks;

    printf("Blockwdh %d \n",msg.wdh); 
    
    if(msgsnd(mid, &msg, sizeof(msg.buffer), 0)==-1){
        perror("msgsnd");
        exit(-1);
    }
    

    if(bufSize != 512) msg.wdh = msg.wdh / (bufSize/512);
    // CHECK: Pruefe ob Quelldatei eine regulaere Datei ist
    if(S_ISREG(bufReadingFile.st_mode) == 0) {
        fprintf(stderr, "Die Quelldatei ist keine requlaere Datei\n");
        exit(EXIT_FAILURE);
    }
    
    
    
    /* Schleife, die entsprechend der Anzahl der Bloecke die Datei
        Stueckweise kopiert */
    for(int kopieren = 0; kopieren < msg.wdh; ++kopieren) {
        // Einlesen bis zum Ende des Puffers (oder der Datei)
        if(read(fd_ReadingFile, msg.buffer, bufSize) == -1) {
            perror("Fehler beim Lesen");
            exit(EXIT_FAILURE);
        }

        //Send message to Message Queue for Server, throws and error for invalid input
        if(msgsnd(mid, &msg, sizeof(msg.buffer), 0)==-1){
            perror("msgsnd");
            exit(-1);
        }

        
    }

    // Schliessen der Filedeskriptoren
    if (close(fd_ReadingFile) == -1) {
        perror("Fehler beim Schliessen der Quelldatei");
        exit(EXIT_FAILURE);
    }

    

    msgctl(mid, IPC_RMID, (struct msqid_ds *) 0);
    return EXIT_SUCCESS;
}
