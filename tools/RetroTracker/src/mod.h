

#ifndef _MOD_SOUND_FORMAT___
#define _MOD_SOUND_FORMAT___

typedef struct
{
	char name[22];
	short length;
	char finetune,volume;
	short loopstart,looplen;


}MOD_SAMPLE;

typedef struct
{
	char name[20];
	char id[4];

	char ordnum,restart;
	char Pattern_Table[128];
}MOD_HEADER;


void mod_print(MOD_HEADER mod);
void mod_print2(MOD_HEADER mod);
void mod_print_sample(MOD_SAMPLE mod,int i);

int mod_convert_note(int note);
int mod_id(char *id);
void mod_resample(unsigned char *data,int len,int type);
void mod_sample_xor(MOD_SAMPLE *mod);
int mod_convert_effect(int effect);

#endif
