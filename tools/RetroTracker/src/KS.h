
#ifndef _KS_SOUND_FORMAT___
#define _KS_SOUND_FORMAT___

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
	unsigned char flags,note,instrument,volume,effect1,effect2;

}KS_FORMAT_PATTERN;

typedef struct
{
	char name[32];
	int length,loop_start,fadeout,enable;
	unsigned char volume,Finetune,type,Panning,Relative,nvolume,npanning,Reserved;

	char Points_volume[8];
	char Points_panning[8];

	char *data_sample;
}KS_FORMAT_INSTRUMENTS;


typedef struct
{
	char id[4],name[28+32];

	unsigned char Nchannels,Ninstruments,tempo,BPM,chFlag;
	int ticks,size_pattern;
	int begin[32];

	KS_FORMAT_INSTRUMENTS *instruments;
	KS_FORMAT_PATTERN **pattern;
	//KS_FORMAT_PATTERN pattern[128][128];
	int rows[256];
	int nrows,size_sample,size_track;

}KS_FORMAT;

void KS_set_header(KS_FORMAT *ks,char *name,unsigned char Nchannels,unsigned char Ninstruments,unsigned char tempo,unsigned char BPM);
void KS_set_pattern(KS_FORMAT *ks,int size);
void KS_savedata_sample(KS_FORMAT *ks,char *str,int *option,unsigned char *data,int i,int loop_start,int length,
						int volume,int relative,int type,int bitssize,int frq);
void KS_delay_fputc(int delay,FILE *out);

void savewav( char *adresse,unsigned char *data,int len,int type,int frq);
int savebrr( char *adresse,unsigned char *data,int len,int type,int dec,int begin,int out);
void output_filename(char *adresse,char *schaine);

void KS_write_track(KS_FORMAT *ks,int *option,int out);
void KS_write_header_SNES(KS_FORMAT *ks,int *option,int out);
void KS_write_SNES_asm(KS_FORMAT *ks,int *option);
void KS_write(KS_FORMAT *ks,int *option);

int KS_compress(unsigned char *data,int len,int type,int lz);
int KS_pitch(int notes);

void SPC_pitch(void);
int loadwav(char *address,WAV *wav);
void SPC_Sample(int *option);
signed short* KS_resample16bits(unsigned char *data,int len,int type);
signed short *KS_resample(signed short *samples, int samples_length, int out_length, char type);
void KS_write_SPC_asm(int num,int offset);
void KS_instruments_init(KS_FORMAT *ks,int i);
int savepcm6b( char *adresse,unsigned char *data,int len,int type,int dec,int begin,int out);
int savepcm5b( char *adresse,unsigned char *data,int len,int type,int dec,int begin,int out);
void KS_write_SNES(KS_FORMAT *ks,int *option);
void KS_write_PCE(KS_FORMAT *ks,int *option);
void KS_write_NG(KS_FORMAT *ks,int *option);

void KS_write_header_PCE(KS_FORMAT *ks,int *option,int out);

void KS_debug_note(int note);

void init_brr(char * str,int mode);
void close_brr();
void offset_brr(int offset);
#define KS_Appregio  0
#define KS_Toneporta 1
#define KS_Vibrato   2
#define KS_Tremolo   3

#define KS_porta_up     4
#define KS_porta_down   5
#define KS_Volume_slide 6
#define KS_Toneporta_Volume_slide 7

#define KS_Vibrato_Volume_slide   8
#define KS_Panning  9
#define KS_Finetune 10
#define KS_Position_jump 11

#define KS_Void0 12
#define KS_Pattern_break 13
#define KS_Void1 14
#define KS_Set_tempo 15

#endif
