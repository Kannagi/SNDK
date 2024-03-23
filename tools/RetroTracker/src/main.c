#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <time.h>

#include "sfc.inc"
#include "KS.h"

int XM_Load(char *name,int *option);
int IT_Load(char *name,int *option);
int S3M_Load(char *name,int *option);
int MOD_Load(char *name,int *option);
int BTM_Load(char *name,int *option);
int LoadMidi(char *path,int next);

int main(int argc, char** argv)
{
	int i = 0;

	if(argc < 1) return 0;

	int option[20];
	for(i = 0; i < 20;i++) option[i] = 0;
	char name[500];
	name[0] = 0;
	option[8] = 4;

	for(i = 1; i < argc;i++)
	{
		if(argv[i][0] == '-')
		{
			if(strcmp(argv[i],"-spcpitch") == 0) option[0] = 1;
			if(strcmp(argv[i],"-owav")     == 0) option[1] = 1;
			if(strcmp(argv[i],"-info")     == 0) option[2] = 1;
			if(strcmp(argv[i],"-mute")     == 0) option[3] = 1;
			if(strcmp(argv[i],"-compress") == 0) option[4] = 1;
			if(strcmp(argv[i],"-compress2")== 0) option[4] = 2;
			if(strcmp(argv[i],"-rom")      == 0) option[5] = 1;
			if(strcmp(argv[i],"-sfxasm")   == 0) option[6] = 1;


			if(strcmp(argv[i],"-sfc")   == 0) option[12] = 0;
			if(strcmp(argv[i],"-pce")   == 0)
			{
				option[8] = 17;
				option[12] = 1;
			}
			if(strcmp(argv[i],"-ng")   == 0) option[12] = 2;

			if(strcmp(argv[i],"-ticks")    == 0)
			{
				i++;
				if(i < argc) option[8] = atoi(argv[i]);
			}
			if(strcmp(argv[i],"-oasm")     == 0)
			{
				i++;
				if(i < argc) option[9] = atoi(argv[i])+1;
			}
			if(strcmp(argv[i],"-sfx")      == 0)
			{
				i++;
				if(i < argc) option[10] = atoi(argv[i])+1;
				i++;
				if(i < argc) option[11] = atoi(argv[i]);
			}


		}else
		{
			strcpy(name,argv[i]);
		}
	}
	option[8] *= 8;

	if(option[0] == 1)
	{
		SPC_pitch();
		return 0;
	}

	if(option[10] > 0)
	{
		SPC_Sample(option);
		return 0;
	}

	if(name[0] == 0)
	{

		printf("Option : -spcpitch -owav -info -mute -compress -compress2 -sfc -sfxasm\n");
		printf("Option + arg : -ticks -oasm\n");
		printf("Option + 2 arg : -sfx\n");
		printf("\n\n");

		printf("-spcpitch\nPrints out the master SPC pitch table. The IT file is not needed in this case.\n");
		printf("-owav\nFor each sample, output a .wav file\n");
		printf("-info\nPrints out information for a module file.\n");
		printf("-mute\nNot implemented yet.\n");
		printf("-compress\nLimits to 4kb samples\n");
		printf("-compress2\nLimits to 2kb samples\n");
		printf("-sfc\nOutputs a SFC file.\n");
		printf("-ticks\nDefines the number of SPC700 timer ticks to use for conversion. Default is 4.\n");
		printf("-oasm\nOutputs an ASM file with the ID specified next to it.\n");
		printf("-sfx\nOutputs SFX samples , name for your Samples : Sample*.wav (* 0-31)\n");
		printf("-sfxasm\nOutputs an ASM file for SFX\n");
		printf("\n\n");
		printf("Example :\nsnesconvert_tracker myfile.xm -oasm 0\n");
		printf("snesconvert_tracker myfile.xm -sfc\n");



		return 0;
	}

	if(option[5] != 0)
	{
		FILE *file = fopen("music.smc","wb");
		if(file != NULL)
		{
			fwrite(SFC_data , 1, SFC_size,file);
			fclose(file);
		}else
		{
			printf("Error.sfc\n");
			return 0;
		}
	}

	if(XM_Load(name,option) == 0)  return 0;
	if(IT_Load(name,option) == 0)  return 0;
	if(MOD_Load(name,option) == 0) return 0;
	if(S3M_Load(name,option) == 0)  return 0;

	//int extract = -1;

	//if(argc == 3) extract = (argv[2][0]-'0')&0x0F;
	//if(LoadMidi(argv[1],extract) == 0) return 0;

	printf("unknow format\n");


    return 0;

}


