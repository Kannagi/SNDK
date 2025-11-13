#include <stdio.h>
#include <stdlib.h>

#include "vgm.h"

#define VGM_TICK 0.022675737f

void VGM_delay(VGM *vgm,FILE *file,int delay)
{
	int tmp;
	static float fdelay = 0;

	fdelay += (float)delay*VGM_TICK;

	while(delay >= 3150)
	{
		fputc(0xFF,file);
		delay -= 3150;
		fdelay -= 73.728f;
		vgm->size+=1;
		vgm->sizet[11]+=1;
	}

	if(fdelay < 0.288f)
		return;

	tmp = fdelay/0.288f;
	fdelay -= 0.288f*(tmp);


	fputc(tmp+8,file);
	vgm->size+=1;
	vgm->sizet[10]+=1;
}

void VGM_delay_old(VGM *vgm,FILE *file,int delaynew)
{
	static int delay = -1;

	int tmp;

	tmp = delay / 12.71;
	tmp -=1;
	if(tmp == -1) tmp = 0;



	if(delay == 735)
	{
		vgm->size+=1;
		vgm->sizet[11]+=1;
		fputc(0x03,file);
		return;
	}

	if(delay == 882)
	{
		vgm->size+=1;
		vgm->sizet[11]+=1;
		fputc(0x04,file);
		return;
	}




	return;

	tmp = delay / 12.71;

	tmp -=1;
	if(tmp == -1) tmp = 0;
	if( (delay < 0x10) && (delay >= 0x00) )
	{
		vgm->size+=1;
		vgm->sizet[5]+=1;
		fputc(0x10+tmp,file);
		return;
	}


	if(delay == delaynew)
	{
		vgm->size+=1;
		vgm->sizet[6]+=1;
		fputc(0x05,file);
		return;
	}

	if(delay != delaynew)
	{
		delay = delaynew;
	}

	if(delay == 0) return;

	fputc(0x06,file);
	fputc(tmp>>8,file);

	return;

	tmp = 0.02275*(float)delay;
	tmp &= 0x07FF;

	printf("delay :: %d %d\n",tmp,delay);

	fputc(0x06,file);
	fputc(tmp>>8,file);
	fputc(tmp&0xFF,file);
	vgm->size+=3;
	vgm->sizet[6]+=3;
}

