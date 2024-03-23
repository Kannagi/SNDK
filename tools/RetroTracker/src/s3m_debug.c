
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdint.h>

#include "KS.h"
#include "s3m.h"

void s3m_print_instrument(S3M_INSTRUMENT s3m,int i)
{
	printf("----------------\n");
	printf("INSTRUMENT : %d\n",i);

	printf("type : %x\n",s3m.type);
	printf("filename : %.12s\n",s3m.filename);


	printf("ptrDataH : %x\n",s3m.ptrDataH);
	printf("ptrDataL : %x\n",s3m.ptrDataL);
	printf("length : %d\n",s3m.length);
	printf("loopStart : %x\n",s3m.loopStart);
	printf("loopEnd : %x\n",s3m.loopEnd);

	printf("volume : %d\n",s3m.volume);
	//printf("reserved : %.4s\n",s3m.reserved);
	printf("pack : %d\n",s3m.pack);
	printf("flags : %d\n",s3m.flags);
	printf("c2spd : %d\n",s3m.c2spd);

	printf("internal : %.12s\n",s3m.internal);
	printf("title : %.28s\n",s3m.title);
	printf("sig : %.4s\n",s3m.sig);

}

void s3m_print(S3M_HEADER s3m)
{
	printf("name : %.28s\n",s3m.name);
	printf("sig : %x\n",s3m.sig);
	printf("type : %x\n",s3m.type);

	printf("orderCount : %d\n",s3m.orderCount);
	printf("instrumentCount : %d\n",s3m.instrumentCount);
	printf("patternPtrCount : %d\n",s3m.patternPtrCount);
	printf("flags : %x\n",s3m.flags);
	printf("trackerVersion : %x\n",s3m.trackerVersion);
	printf("sampleType : %d\n",s3m.sampleType);

	printf("sig2 : %.4s\n",s3m.sig2);

	printf("globalVolume : %d\n",s3m.globalVolume);
	printf("initialSpeed : %d\n",s3m.initialSpeed);
	printf("initialTempo : %d\n",s3m.initialTempo);
	printf("masterVolume : %d\n",s3m.masterVolume);
	printf("ultraClickRemoval : %d\n",s3m.ultraClickRemoval);
	printf("defaultPan : %d\n",s3m.defaultPan);

	printf("ptrSpecial : %d\n",s3m.ptrSpecial);
}
