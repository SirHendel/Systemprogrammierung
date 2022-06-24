#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
#include "msg_struct.h"

void cleanup();

//Message-Queue-ID
int msqid;
//Dateideskriptor zur Quelldatei
int fd_source;

int main(int argc, char* argv[]) {
  int byteGelesen = 0,byteGeschrieben = 0;
  key_t sysVkey;
	
	
	
  struct stat datEig;
	
  struct msgHandshake handshake;
  struct msgHandshakeAccept handshakeAccept;
  struct msgFileSend msgSend;
  struct msgFileRcv msgRcv;
  struct msgCancel msgCancl;
  int id = 0;
	
  handshake.mtype = HANDSHAKE;
  msgSend.mtype = SENDING;
  msgCancl.mtype = CANCEL;
	
  if(argc != 4) {
    fprintf(stderr, "Aufruf: Client <servername> <Quelldatei> <Zieldatei>");
    exit(EXIT_FAILURE);
  }
  //Quelldatei lesend öffnen
  fd_source = open(argv[2],O_RDONLY);
  if (fd_source < 0) {
    perror("open : ");
    exit(EXIT_FAILURE);
  }
	
  //Dateieigenschaften beschaffen
  if (fstat(fd_source,&datEig) < 0) {
    perror("fstat : ");
    exit(EXIT_FAILURE);
  }
	
  //SysV IPC Key generieren mit Server-Executable
  if ((sysVkey = ftok(argv[1],1)) < 0) {
    perror("FtoK : ");
    exit(EXIT_FAILURE);
  }
  //Message-Queue-ID erhalten
  if ((msqid = msgget(sysVkey,0)) < 0) {
    perror("msgget : ");
    exit(EXIT_FAILURE);
  }
	
  //Aufräum-Methode installieren
  atexit(cleanup);
	
  //Cancel-Nachricht vorbereiten
  msgCancl.mtype = CANCEL;
  msgCancl.reason = 1;
	
  /* ********* *
   * Handshake *
   * ********* */
	
  //Handshake-Message vorbereiten
  handshake.mtype = HANDSHAKE;
  strncpy(handshake.fn.filename,argv[3],BUFFER_SIZE);
  handshake.fn.fileNameLength = sizeof(argv[2]);
  handshake.fn.filesize = datEig.st_size;
  handshake.fn.filerights = datEig.st_mode;
  if (msgsnd(msqid,&handshake,sizeof(struct fileName),0) < 0) {
    perror("Fehler beim senden des handshakes : ");
    exit(EXIT_FAILURE);
  }
  printf("Warte auf Antwort vom Server...\n");
  if (msgrcv(msqid,&handshakeAccept,sizeof(handshakeAccept),HANDSHAKE_CONFIRM,0) < 0) {
    perror("Empfangen vom handshake-Fehler : ");
    exit(EXIT_FAILURE);
  }
  printf("Antwort erhalten!\n");
  //Wenn Server Ablehnung schickt, abbrechen mit Fehlermeldung
  if (handshakeAccept.fn.resultcode != 0) {
    fprintf(stderr,"Die Datei '%s' konnte nicht erstellt werden"
	    ",da Datei bereits vorhanden!\n",argv[3]);
    exit(EXIT_FAILURE);
  }
	
  /* *************** *
   * Datei versenden *
   * *************** */
  while ((byteGelesen = read(fd_source,msgSend.data.inhalt,BUFFER_SIZE)) != 0) {
    if (byteGelesen < 0) {
      perror("Lesefehler: ");
      //Fehlermeldung schicken
      msgsnd(msqid,&msgCancl,sizeof(msgCancl.reason),0);
      exit(EXIT_FAILURE);
    }
		
    //Prüfen, ob Fehlernachrichten vorliegen
    if (msgrcv(msqid,&msgCancl,sizeof(msgCancl.reason),CANCEL,IPC_NOWAIT) >= 0) {
      fprintf(stderr," Serverfehler!\n");
      exit(EXIT_FAILURE);
    }
		
    msgSend.data.inhaltgroesse = byteGelesen;
    msgSend.data.id = id;
    //Datei-Teil versenden
    if (msgsnd(msqid,&msgSend,sizeof(msgSend.data),0) < 0) {
      perror("Problem mit dem Senden: ");
      exit(EXIT_FAILURE);
    }
		
    //Auf Empfangsbestätigung warten
    if (msgrcv(msqid,&msgRcv,sizeof(msgRcv.data),0,0) < 0) {
      perror("Empfangsbestätigung-Fehler-Meldung: ");
      exit(EXIT_FAILURE);
    }
    //Wenn Server Paket nicht bestätigt
    if (msgRcv.data.resultcode != 0) {
      fprintf(stderr,"Server hat ein Problem festgestellt! Abbruch!\n");
      exit(EXIT_FAILURE);
    }
		
		
    //Nächstes Paket vorbereiten
    id++;
  }
  printf("Datei '%s' vollständig an Server gesendet!\n",argv[2]);
	
  /* ************************ *
   * Vom Server verabschieden *
   * ************************ */
  printf("Verbindung wird beendet..\n");
  if (msgrcv(msqid,&msgCancl,sizeof(msgCancl.reason),CANCEL,0) < 0) {
    perror("msgrcv wird abgebrochen ");
    exit(EXIT_FAILURE);
  }
  msgCancl.reason = 0;
  if (msgsnd(msqid,&msgCancl,sizeof(msgCancl.reason),0) < 0) {
    perror("msgsnd wird abgebrochen: ");
    exit(EXIT_FAILURE);
  }
  printf("Vom Server getrennt!\n");
  return EXIT_SUCCESS;
}

void cleanup() {
  //Quelldatei schließen
  close(fd_source);
}
