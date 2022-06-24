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
	//Nur wenn Message-Queue angelegt wurde
	printf("Raus!\n");
	printf("MSQID: %d\n",msqid);
	if (msqid >= 0) {
		//Message-Queue entfernen
		if ((msgctl(msqid,IPC_RMID,NULL)) < 0) {
			perror("msgctl : ");
			_exit(EXIT_FAILURE);
		}
	}
	//Offene Datei schließen
	close(fd_dest);
}

//INT-Signal-Handler
static void sig_handler(int sig) {
	//Aufrufen des Exit-Handlers
	printf("\nSignal %d empfangen \n",sig);
	exit(EXIT_SUCCESS);
}

int main(int argc, char* argv[]) {
	key_t sysVkey;
	
	
	
	//Signalhandling für Ctrl+C
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
	
	//Fehlerhandler installieren
	atexit(exitHandler);
	
	/* ************************* *
	 * Signal-Handler für Ctrl+C *
	 * ************************* */
	//Installiere Handler für INT-Signal
	act.sa_handler = sig_handler;
	act.sa_flags = 0;	
	//Signalmenge erzeugen
	if (sigemptyset(&act.sa_mask) < 0) {
		perror("SigEmptySet : ");
		exit(EXIT_FAILURE);
	}
	//Der Signalmenge das INT-Signal anfügen
	if (sigaddset(&act.sa_mask,SIGINT) < 0) {
		perror("SigAddSet : ");
		exit(EXIT_FAILURE);
	}
	//Signalmaske für Programm setzen
	if (sigprocmask(SIG_UNBLOCK,&act.sa_mask,NULL) < 0) {
		perror("SigProcMask : ");
		exit(EXIT_FAILURE);
	}
	
	//Signal SIGKILL auswerten lassen
	if (sigaction(SIGINT, &act, NULL) < 0) {
		perror("SigAction : ");
		exit(EXIT_FAILURE);
	}
	
	
	/* ************* *
	 * Message-Queue *
	 * ************* */
	//Eindeutigen Schlüssel erhalten
	if ((sysVkey = ftok(argv[0],1)) < 0) {
		perror("ftok : ");
		exit(EXIT_FAILURE);
	}
	
	//Message-Queue erstellen
	if ((msqid = msgget(sysVkey,IPC_CREAT|0600)) < 0) {
		perror("msgget : ");
		exit(EXIT_FAILURE);
	}
	printf("MSQID: %d\n",msqid);
	printf("Server läuft...\n");
	
	
	/* *********************** *
	 * Bearbeiten von Anfragen *
	 * *********************** */
	while(1) {
		printf("\nWarten auf weitere Verbindungen...\n");
		filesize = 0; 
		//Auf Handshake warten
		if (msgrcv(msqid,&handshake,sizeof(handshake.fn),
					HANDSHAKE,0) < 0){
			perror("msgrcv : ");
			exit(EXIT_FAILURE);
		}
		printf("Handshake empfangen \n");
		//Wenn Datei bereits vorhanden, Kopieren ablehnen
		if ((fd_dest = open(handshake.fn.filename,
					O_WRONLY|O_CREAT|O_EXCL)) < 0) {
			//Kopieren ablehnen
			handshakeAccept.fn.resultcode = 1;
			printf("Abgelehnte Datei '%s'\n",handshake.fn.filename);
		} else {
			//Kopiervorgang akzeptieren
			handshakeAccept.fn.resultcode = 0;
			printf("Akzeptierte Datei '%s'\n",handshake.fn.filename);
		}
		//Antwort senden
		if (msgsnd(msqid,&handshakeAccept,
					sizeof(handshakeAccept.fn),0) < 0) {
			perror("msgsnd handshake : ");
			exit(EXIT_FAILURE);
		}
		printf("Handshake Antwort wird gesendet\n");
		//Wenn Handshake abgelehnt, auf neuen Handshake warten
		if (handshakeAccept.fn.resultcode == 1) {
			continue;
		}
		
		//Dateigröße speichern
		filesize = handshake.fn.filesize;
		printf("Datei mit %d Bytes wird empfangen...\n",filesize);
		printf("[\n");
		//Auf Dateiinformationen warten
		while(filesize > 0) {
			if (msgrcv(msqid,&msgSend,sizeof(msgSend.data),
					SENDING,0) < 0) {
				perror("msgrcv Dateiinfo : ");
			}
			//Daten schreiben
			if (write(fd_dest,msgSend.data.inhalt,
					msgSend.data.inhaltgroesse) < 0) {
				perror("Schreibfehler: ");
				//Abbruchmeldung senden
				msgRcv.data.resultcode = 1;
			} else {
				//Rechte anpassen
				chmod(handshake.fn.filename,handshake.fn.filerights);
				//Bestätigung senden
				msgRcv.data.resultcode = 0;
			}
			
			
			msgRcv.data.id = msgSend.data.id;
			//printf("\tReceived packet %d\tHash: %s\n",msgRcv.data.id,msgRcv.data.hashConfirm);
			printf("\tEmpfangenes Paket %d\n",msgRcv.data.id);
			//Bestätigung senden
			if (msgsnd(msqid,&msgRcv,sizeof(msgRcv.data),0) < 0) {
				perror("msgsnd- fehler Dateiübertragung: ");
				exit(EXIT_FAILURE);
			}
			if (msgRcv.data.resultcode == 1) {
				exit(EXIT_FAILURE);
			}
			//Prüfen, ob Fehlermeldungen vorliegen
			if (msgrcv(msqid,&msgCancl,sizeof(msgCancl.reason),CANCEL,IPC_NOWAIT) > 0) {
				fprintf(stderr,"Nachricht beschädigt! Abbrechen!\n");
				exit(EXIT_FAILURE);
			}
			//Verbleibende Dateigröße anpassen
			filesize -= msgSend.data.inhaltgroesse;
		}
		printf("]\n");
		printf("Empfangene Datei '%s'!\n",handshake.fn.filename);
		msgCancl.reason = 0;
		if (msgsnd(msqid,&msgCancl,sizeof(msgCancl.reason),0) < 0) {
			perror("msgsnd Abbruch: ");
			exit(EXIT_FAILURE);
		}
		printf("Verbindung beenden...\n");
	}
	
	return EXIT_SUCCESS;
}
