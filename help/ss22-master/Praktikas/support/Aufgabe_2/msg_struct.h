//Puffergröße
#define BUFFER_SIZE 1024

//Aufzählung der verschiedenen Nachricht-Typen
enum {
	HANDSHAKE = 1,
	HANDSHAKE_CONFIRM,
	SENDING,
	SENDING_CONFIRM,
	CANCEL,
	EXIT
};

/* Struktur zur Beschreibung des Dateinamens */
struct fileName {
	int resultcode;
	int fileNameLength;
	int filesize;
	int filerights;
	char filename[BUFFER_SIZE];
};

/* Struktur zur Beschreibung des Dateiinhalts */
struct dateiInhalt {
	int id;
	int inhaltgroesse;
	char inhalt[BUFFER_SIZE];	
};

/* Struktur zur Bestätigung des empfangenen Dateiinhalts */
struct dateiInhaltConfirm {
	int id;
	int resultcode;
	
};

/* Struktur zum Beenden der Verbindung */
struct msgCancel {
	long mtype;
	int reason;
};

/* Struktur zum Bestätigen eines Teils einer Datei */
struct msgFileRcv {
	long mtype;
	struct dateiInhaltConfirm data;
};

/* Struktur zum Senden eines Teils einer Datei */
struct msgFileSend {
	long mtype;
	struct dateiInhalt data;
};

/* Struktur zum Verbinden zum Server */
struct msgHandshake {
	long mtype;       /* message type */
	struct fileName fn;    /* message data */
};

/* Struktur zum Akzeptieren des Handshakes */
struct msgHandshakeAccept {
	long mtype;
	struct fileName fn;
};
