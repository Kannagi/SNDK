#include <stdio.h>
#include <stdlib.h>

#include "vgm.h"


int main(int argc, char *argv[])
{
    if (argc < 2)
    {
		printf("Error argument !\n");
		return 1;
    }

    FILE *file = NULL;
	file = fopen(argv[1],"rb");

    if(file == NULL)
	{
		printf("Error no open file!\n");
		return 1;
	}

	fseek(file, 0, SEEK_END);
	int size = ftell(file);

	fseek(file, 0, SEEK_SET);

	unsigned char *buffer = (unsigned char *)malloc(size+3);
	if (buffer == NULL)
	{
		fclose(file);
		printf("Error malloc!\n");
		return 1;
	}

	fread(buffer, 1,size, file);
	fclose(file);

	VGM vgm;
	vgm.tag = 0;
	if(buffer[0] == 'V') vgm.tag++;
	if(buffer[1] == 'g') vgm.tag++;
	if(buffer[2] == 'm') vgm.tag++;
	if(buffer[3] == ' ') vgm.tag++;

	if(vgm.tag != 4)
	{
		printf("Error no VGM File!\n");
		return 1;
	}

	int *buffer32 = (void*)buffer;

	vgm.eof = buffer32[1];
	vgm.version = buffer32[2];

	vgm.gd3 = buffer32[5]+20-1;
	vgm.totalsample = buffer32[6];
	vgm.loopoffset = buffer32[7];

	vgm.loopsample = buffer32[8];
	vgm.rate = buffer32[9];

	vgm.data = buffer32[13];

	vgm.YM2608 = buffer32[18];
	vgm.YM2610 = buffer32[19];
	vgm.RF5C68 = buffer32[16];
	vgm.RF5C164 = buffer32[27];

	printf("EOF %x\n",vgm.eof);
	printf("Version %x\n",vgm.version);
	printf("GD3 %x\n",vgm.gd3);

	printf("Total Samples %d\n",vgm.totalsample);
	printf("Loop offset %x\n",vgm.loopoffset);
	printf("Loop Samples %d\n",vgm.loopsample);

	printf("Rate %d\n",vgm.rate);

	printf("Data offset %x\n",vgm.data+52);

	printf("YM2608 %d\n",vgm.YM2608);
	printf("YM2610 %d\n",vgm.YM2610);
	printf("RF5C68 %d\n",vgm.RF5C68);
	printf("RF5C164 %d\n",vgm.RF5C164);


	printf("----------\n");

	char outname[0x100];
	sprintf(outname,"%sx",argv[1]);

	int sizepcm = 0;
	if(argc == 3)
	{
		sizepcm = atoi(argv[2]);
	}


	//NEO GEO
	if(vgm.YM2610 != 0)
	{
		VGM_Read_YM(vgm,buffer,outname,sizepcm);
		return 0;
	}

	//RICOH (SNES)
	if( (vgm.RF5C68 != 0) | (vgm.RF5C164 != 0) )
	{

		VGM_Read_RICOH1(vgm,buffer,outname,sizepcm);
		return 0;
	}

	printf("Error no VGM Supported!\n");

	return 1;
}


void VGM_Init(VGM *vgm)
{
	vgm->size = 0;

	int l;

	for(l = 0;l < 0x100;l++)
	{
		vgm->port0[l] = -1;
		vgm->port1[l] = -1;
	}

	for(l = 0;l < 12;l++)
		vgm->sizet[l] = 0;

	for(l = 0;l < 16;l++)
		vgm->inst[l] = 0;

	for(l = 0;l < 17;l++)
		vgm->spc700[l] = 0;

	vgm->spc700[15] = 0xF7;
	vgm->spc700[16] = 0x01;
	vgm->spc700[0] = 0x20;


	for(l = 0;l < 32;l++)
	{
		vgm->adsr1[l] = 0x7F;
		vgm->adsr2[l] = 0xE0;
		vgm->gain[l]  = 0x3F;
	}
}

void VGM_Print_size2(VGM *vgm)
{
	printf("ENV %d bytes\n",vgm->sizet[0]);
	printf("PAN %d bytes\n",vgm->sizet[1]);
	printf("FDL %d bytes\n",vgm->sizet[2]);
	printf("FDH %d bytes\n",vgm->sizet[3]);
	printf("LSL %d bytes\n",vgm->sizet[4]);
	printf("LSH %d bytes\n",vgm->sizet[5]);
	printf("ST  %d bytes\n",vgm->sizet[6]);
	printf("CRG %d bytes\n",vgm->sizet[7]);
	printf("CH  %d bytes\n",vgm->sizet[8]);

	printf("Wait %d ticks\n",vgm->sizet[10]);

	printf("Total %d bytes\n",vgm->size);
}


void VGM_Print_size(VGM *vgm)
{
	printf("ADPCM-A %d bytes\n",vgm->sizet[0]);
	printf("ADPCM-B %d bytes\n",vgm->sizet[1]);
	printf("SSG %d bytes\n",vgm->sizet[2]);
	printf("FM Commons %d bytes\n",vgm->sizet[3]);
	printf("FM OP %d bytes\n",vgm->sizet[4]);
	printf("Wait %d bytes\n",vgm->sizet[11]);

	printf("Wait1 %d bytes\n",vgm->sizet[10]);
	printf("Wait2 %d bytes\n",vgm->sizet[11]);

	printf("Total %d bytes\n",vgm->size);
}

