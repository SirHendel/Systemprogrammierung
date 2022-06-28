#if !defined(__SOCKBSP_H)
#define __SOCKBSP_H
#define ORDER_SOCKET "/tmp/mysocket" 
#define BUFFER_SIZE 1024
#include <sys/stat.h>

struct order { //beschreibt die den Kopier inhalt
	int filesize;
	int filerights;
	int id;
	int resultcode;
	mode_t bufReadingFile;
	char filename[BUFFER_SIZE];
};

struct content{ //beschreibt die den Kopier inhalt
	int id;
	int Contentsize;
	char buffer[BUFFER_SIZE];
};


struct result {
	int id;
	int resultcode;
};
#endif

