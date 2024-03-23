
#ifndef _XM_SOUND_FORMAT___
#define _XM_SOUND_FORMAT___


typedef struct
{
	int header_length;
	char type;
	short Nrowspattern;
	short size;

	char *data;

}XM_PATTERNS;

typedef struct
{
	int header_size;
	char number_notes[96];
	char Points_volume[48];
	char Points_panning[48];

	char nvolume,npanning,vsustain,vloop_start,vloop_end,psustain,ploop_start,ploop_end;
	char volume,panning;
	char type,sweep,depth,rate;
	short fadeout,Reserved;


}XM_INSTRUMENTS_EXT;

typedef struct
{
	int length,loop_start,loop_length;
	char Volume,Finetune,type,Panning,Relative,Reserved;
	char name[22];

}XM_SAMPLE;

typedef struct
{
	int size;
	char name[22];
	char type;
	short Nsamples;

	XM_INSTRUMENTS_EXT ext;

}XM_INSTRUMENTS;

typedef struct
{
	char ID_text[17];
	char Module_name[20];
	char x;
	char Tracker_name[20];
	short Version_number;
	int Header_size;

	short Song_length,Restart_position,Nchannels,Npatterns,Ninstruments,Flags,tempo,BPM;

	char Pattern_table[256];


	XM_PATTERNS **patterns;
	XM_INSTRUMENTS **instruments;

}XM_HEADER;

void xm_resample(unsigned char *data,int len,int type);

void xm_print_instruments(XM_HEADER xm,int i);
void xm_print_instruments_ext(XM_HEADER xm,int i);
void xm_print_samples(XM_SAMPLE xm_sample,int i);
void xm_print_patterns(XM_HEADER xm,int i);
void xm_print(XM_HEADER xm);
int xm_convert_effect(int effect);

#endif

