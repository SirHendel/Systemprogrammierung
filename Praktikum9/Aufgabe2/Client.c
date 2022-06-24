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
  int readbyte = 0;

  key_t ftok=(".", 'z');
	
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
	
  if(argc != 3) {
    fprintf(stderr, "Quell- und Zieldatei angebebn");
    exit(EXIT_FAILURE);
  }
  fd_source = open(argv[1],O_RDONLY);
  if (fd_source < 0) {
    perror("open");
    exit(EXIT_FAILURE);
  }
	
  //Message-Queue-ID 
  if ((msqid = msgget(ftok,0)) < 0) {
    perror("msgget");
    exit(EXIT_FAILURE);
  }

	if (fstat(fd_source,&datEig) < 0) {
    perror("fstat");
    exit(EXIT_FAILURE);
  }
  //install Aufräum-Methode 
  atexit(cleanup);
	
  //prepare Cancel-Nachricht 
  msgCancl.mtype = CANCEL;
  msgCancl.reason = 1;
	
  //prepare Handshake-Message 
  handshake.mtype = HANDSHAKE;
  strncpy(handshake.fn.filename,argv[2],BUFFER_SIZE);
  handshake.fn.fileNameLength = sizeof(argv[1]);
  handshake.fn.filesize = datEig.st_size;
  handshake.fn.filerights = datEig.st_mode;

  if (msgsnd(msqid,&handshake,sizeof(struct fileName),0) < 0) {
    perror("handshakes : ");
    exit(EXIT_FAILURE);
  }
  if (msgrcv(msqid,&handshakeAccept,sizeof(handshakeAccept),HANDSHAKE_CONFIRM,0) < 0) {
    perror("handshake: ");
    exit(EXIT_FAILURE);
  }
  if (handshakeAccept.fn.resultcode != 0) {
    fprintf(stderr,"Die Datei ist bereits vorhanden");
    exit(EXIT_FAILURE);
  }
  while ((readbyte = read(fd_source,msgSend.data.content,BUFFER_SIZE)) != 0) {
    if (readbyte < 0) {
      perror("Lesefehler");
      msgsnd(msqid,&msgCancl,sizeof(msgCancl.reason),0);
      exit(EXIT_FAILURE);
    }
    if (msgrcv(msqid,&msgCancl,sizeof(msgCancl.reason),CANCEL,IPC_NOWAIT) >= 0) {
      fprintf(stderr," Serverfehler\n");
      exit(EXIT_FAILURE);
    }
    msgSend.data.contentsize = readbyte;
    msgSend.data.id = id;
    if (msgsnd(msqid,&msgSend,sizeof(msgSend.data),0) < 0) {
      perror("Senden error");
      exit(EXIT_FAILURE);
    }
		
    if (msgrcv(msqid,&msgRcv,sizeof(msgRcv.data),0,0) < 0) {
      perror("Receive error");
      exit(EXIT_FAILURE);
    }
    if (msgRcv.data.resultcode != 0) {
      fprintf(stderr,"Server errorr\n");
      exit(EXIT_FAILURE);
    }
    id++;
  }
  if (msgrcv(msqid,&msgCancl,sizeof(msgCancl.reason),CANCEL,0) < 0) {
    perror("msgrcv");
    exit(EXIT_FAILURE);
  }
  msgCancl.reason = 0;
  if (msgsnd(msqid,&msgCancl,sizeof(msgCancl.reason),0) < 0) {
    perror("msgsnd");
    exit(EXIT_FAILURE);
  }
  return EXIT_SUCCESS;
}

void cleanup() {
  close(fd_source);
}
