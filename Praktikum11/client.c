#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <stddef.h>
#include "sockbsp.h"
#include <signal.h>
#include <math.h>
#include <fcntl.h>


int main(int argc, char *argv[])
{
  int sockfd;
  int addrlen;
  int nwritten, nread;
  int fd_source;
  int readbyte;

  struct order order;
  struct content content;
  struct result result;
  struct sockaddr_un server_addr;
  struct stat data;

  /* Kommandozeilenparameter werden über prüft */ 
  if(argc != 3) {
    fprintf(stderr, "Aufruf: %s  Quelle- Zieldatei \n", argv[0]);
    exit(EXIT_FAILURE);
  }

  /* Socket anlegen */
  if((sockfd = socket(PF_LOCAL, SOCK_STREAM, 0)) < 0) {
    perror("socket");
    exit(EXIT_FAILURE);
  }

  /* Adresse vorbereiten */
  server_addr.sun_family = AF_LOCAL;
  strncpy(server_addr.sun_path,  ORDER_SOCKET, sizeof(server_addr.sun_path)-1);
  addrlen = strlen(server_addr.sun_path) + offsetof(struct sockaddr_un, sun_path);

  /* Verbindung herstellen */
  if(connect(sockfd, (struct sockaddr *)&server_addr, addrlen) < 0) {
    perror("connect");
    exit(EXIT_FAILURE);
  }

  /* öffnen der Quelle datei*/ 
  if((fd_source = open(argv[1],O_RDONLY)) < 0){
    perror("open");
    exit(EXIT_FAILURE);
  } 

  /* fstat lesen der Datei info */
  if(fstat(fd_source, &data) ==-1){
    perror("fstat error");
    exit(EXIT_FAILURE);
  }

  order.bufReadingFile = data.st_mode;
  /* copieren des dateinames auf den Auftrag */
  strncpy(order.filename,argv[2],BUFFER_SIZE);

  /* Auftrag senden */
  if((nwritten = write(sockfd, &order, sizeof(struct order))) < 0) {
    perror("write");
    exit(EXIT_FAILURE);
  }
  
  /* Lesen und sende der Datei Inhalte */
  while((readbyte = read(fd_source,content.buffer,BUFFER_SIZE)) != 0){
    /* Lese überprüfung */
    if(readbyte < 0){
      perror("lesefehler");
      exit(EXIT_FAILURE);
    }

    content.Contentsize = readbyte;
    /* senden und prüfung */
    if((nwritten = write(sockfd, &content, sizeof(struct content))) < 0) {            
      perror("write ");
      exit(EXIT_FAILURE);
    } 
  }
    
  /* auf Ergebnis warten */
  if((nread = read(sockfd, &result, sizeof(struct result))) < 0) {
    perror("read");
    exit(EXIT_FAILURE);
  }
  /* schliessen der Datei */
  close(fd_source);

  /* Socket schließen */
  if(close(sockfd) < 0) {
   perror("close");
   exit(EXIT_FAILURE);
  }
  /* all Good */
  return EXIT_SUCCESS;
}