#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

#include "KS.h"

void KS_debug_note(int note)
{

		if((note%12) == 0)
			printf("C-");

		if((note%12) == 1)
			printf("C#");

		if((note%12) == 2)
			printf("D-");

		if((note%12) == 3)
			printf("D#");

		if((note%12) == 4)
			printf("E-");

		if((note%12) == 5)
			printf("F-");

		if((note%12) == 6)
			printf("F#");

		if((note%12) == 7)
			printf("G-");

		if((note%12) == 8)
			printf("G#");

		if((note%12) == 9)
			printf("A-");

		if((note%12) == 10)
			printf("A#");

		if((note%12) == 11)
			printf("B-");

		printf("%d ,",note/12);

}

void KS_debug(int pattern,int note,int index,int volume,int effect1,int effect2)
{
	if(note == 0) printf("Key Off ");
	if( (pattern&0x01) && (note != 0) )
	{
		if((note%12) == 0)
			printf("C-");
		if((note%12) == 1)
			printf("C#");

		if((note%12) == 2)
			printf("D-");

		if((note%12) == 3)
			printf("D#");

		if((note%12) == 4)
			printf("E-");

		if((note%12) == 5)
			printf("F-");

		if((note%12) == 6)
			printf("F#");

		if((note%12) == 7)
			printf("G-");

		if((note%12) == 8)
			printf("G#");

		if((note%12) == 9)
			printf("A-");

		if((note%12) == 10)
			printf("A#");

		if((note%12) == 11)
			printf("B-");

		printf("%d ",note/12);

	}
	if(pattern&0x02) printf("i:%x ",index);
	if(pattern&0x04) printf("v:%x ",volume);
	if(pattern&0x08) printf("e:%x",effect1);
	if(pattern&0x10) printf("%x",effect2);
	printf(",");
}
