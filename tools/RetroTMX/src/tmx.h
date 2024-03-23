


typedef struct
{
	char name[64];
	int width,height,encoding;
	unsigned int *data;

}LAYER;


typedef struct
{
	char name[64];
	char source[64];
	int firstgid;
	int tilewidth,tileheight,tilecount,columns;
	int width,height,trans;
}TILESET;

typedef struct
{
	float version,tiledversion;
	int orientation,renderorder,width,height;
	int tilewidth,tileheight,infinite,nextobjectid;
}MAP;


typedef struct
{
	float xmlversion;
	int encoding;
	int nmap,ntileset;
	MAP map;
	TILESET tileset[4096];
	LAYER layer[16];
}TMX;

typedef struct
{
	unsigned short type,x, y;
}TAG;

void Load_TMX(TMX *tmx,char *address);
