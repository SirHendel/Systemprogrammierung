#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
#include <signal.h>
#include "msg_struct.h"

//Message-Queue-ID
int msqid;
//File-Deskriptor
int fd_dest;

void exitHandler() {
	if (msqid >= 0) {
		if ((msgctl(msqid,IPC_RMID,NULL)) < 0) {
			perror("msgctl : ");
			_exit(EXIT_FAILURE);
		}
	}
	close(fd_dest);
}

static void sig_handler(int sig) {
	exit(EXIT_SUCCESS);
}

int main(int argc, char* argv[]) {
	key_t ftok=(".", 'z');

	struct sigaction act;
	struct msgHandshake handshake;
	struct msgHandshakeAccept handshakeAccept;
	struct msgFileSend msgSend;
	struct msgFileRcv msgRcv;
	struct msgCancel msgCancl;
	int filesize = 0;
	
	handshakeAccept.mtype = HANDSHAKE_CONFIRM;
	msgRcv.mtype = SENDING_CONFIRM;
	msgCancl.mtype = CANCEL;
	
	atexit(exitHandler);
	
	act.sa_handler = sig_handler;
	act.sa_flags = 0;	

	if (sigemptyset(&act.sa_mask) < 0) {
		perror("sigemptyset");
		exit(EXIT_FAILURE);
	}
	if (sigaddset(&act.sa_mask,SIGINT) < 0) {
		perror("sigaddset");
		exit(EXIT_FAILURE);
	}
	if (sigprocmask(SIG_UNBLOCK,&act.sa_mask,NULL) < 0) {
		perror("sigprocmask");
		exit(EXIT_FAILURE);
	}
	if (sigaction(SIGINT, &act, NULL) < 0) {
		perror("sigaction");
		exit(EXIT_FAILURE);
	}
	
	if ((msqid = msgget(ftok,IPC_CREAT|0600)) < 0) {
		perror("msgget");
		exit(EXIT_FAILURE);
	}
	while(1) {
		filesize = 0; 
		if (msgrcv(msqid,&handshake,sizeof(handshake.fn),
					HANDSHAKE,0) < 0){
			perror("msgrcv");
			exit(EXIT_FAILURE);
		}
		if ((fd_dest = open(handshake.fn.filename,O_WRONLY|O_CREAT|O_EXCL)) < 0) {
			handshakeAccept.fn.resultcode = 1;
		} else {
			handshakeAccept.fn.resultcode = 0;
		}
		//Antwort senden
		if (msgsnd(msqid,&handshakeAccept,
					sizeof(handshakeAccept.fn),0) < 0) {
			perror("msgsnd");
			exit(EXIT_FAILURE);
		}
		if (handshakeAccept.fn.resultcode == 1) {
			continue;
		}
		filesize = handshake.fn.filesize;
		while(filesize > 0) {
			if (msgrcv(msqid,&msgSend,sizeof(msgSend.data),SENDING,0) < 0) {
				perror("msgrcv Dateiinfo");
			}
			if (write(fd_dest,msgSend.data.content,msgSend.data.contentsize) < 0) {
				perror("Schreiberror");
				msgRcv.data.resultcode = 1;
			} else {
				chmod(handshake.fn.filename,handshake.fn.filerights);
				msgRcv.data.resultcode = 0;
			}
			
			msgRcv.data.id = msgSend.data.id;
			if (msgsnd(msqid,&msgRcv,sizeof(msgRcv.data),0) < 0) {
				perror("msgsnd");
				exit(EXIT_FAILURE);
			}
			if (msgRcv.data.resultcode == 1) {
				exit(EXIT_FAILURE);
			}
			if (msgrcv(msqid,&msgCancl,sizeof(msgCancl.reason),CANCEL,IPC_NOWAIT) > 0) {
				fprintf(stderr, "msgrcv \n");
				exit(EXIT_FAILURE);
			}
			filesize -= msgSend.data.contentsize;
		}
		msgCancl.reason = 0;
		if (msgsnd(msqid,&msgCancl,sizeof(msgCancl.reason),0) < 0) {
			perror("msgsnd");
			exit(EXIT_FAILURE);
		}
	}
	return EXIT_SUCCESS;
}
