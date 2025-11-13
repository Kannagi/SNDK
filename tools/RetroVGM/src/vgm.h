

typedef struct
{
    char FileTypeBlocID[4]; //RIFF
    int size;
    char FileFormatID[4]; //WAVE

    char FormatBlocID[4]; //fmt
    int blocsize; //Nombre d'octets du bloc - 16

    short format; //format 1 = PCM
    short ncanaux; //Nombre de canaux
    int frequence; //frequence
    int BytePerSec; //Nombre d'octets à lire par seconde
    short BytePerBloc; //Nombre d'octets par bloc d'échantillonnage
    short BitsPerSample; //Nombre de bits utilisés pour le codage de chaque échantillon

    char DataBlocID[4]; //Constante «data»
    int DataSize; //Nombre d'octets des données
    unsigned char *data;
}WAV;

typedef struct
{
	int tag,eof,version,gd3,totalsample,loopoffset;
	int loopsample,rate,data,YM2608,YM2610,RF5C68,RF5C164;
	int size;
	int sizet[12];
	int inst[0xFF];

	int port0[0x100],port1[0x100];
	unsigned char spc700[17],adsr1[32],adsr2[32],gain[32];
}VGM;

int  VGM_Load(void);
void VGM_Read_YM(VGM vgm,unsigned char *buffer,char *outname,int pcm);

int VGM_cmd_unk(int cmd);
int VGM_data_pcm(int i,unsigned char *buffer,FILE *file,int wr);
void VGM_delay(VGM *vgm,FILE *file,int delaynew);
void VGM_Init(VGM *vgm);
void VGM_Print_size(VGM *vgm);
void VGM_Print_size2(VGM *vgm);
void VGM_Read_RICOH1(VGM vgm,unsigned char *buffer,char *outname,int pcm);
int VGM_data_pcm_ricoh(int i,unsigned char *buffer,VGM *vgm,int wr,FILE *file);
void load_option(VGM *vgm);
