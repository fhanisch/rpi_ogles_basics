//bmp_rw.h
//Erstellt: 03.01.2016

typedef struct
{	
	//char signature[2];	//2 byte
	//muss weggelassen werden, da vermutlich auf dem RPi nur vielfache von vier adressiert werden können!!!
	uint fileSize;		//4 byte	
	uint reserved;		//4 byte
	uint offset;		//4 byte
	uint infoHeaderSize;	//4 byte
	int xSize;		//4 byte
	int ySize;		//4 byte
	ushort planes;		//2 byte
	ushort farbtiefe;	//2 byte
	uint compression;	//4 byte
	uint bildSize;		//4 byte
	int XPelsPerMeter;	//4 byte
	int YPelsPerMeter;	//4 byte
	uint ClrUsed;		//4 byte	
	uint ClrImportant;	//4 byte
} BMP_HEADER;
