
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <time.h>

#include "KS.h"
#include "mod.h"

void mod_print(MOD_HEADER mod)
{
	printf("name : %.20s\n",mod.name);
	printf("id : %.4s\n",mod.id);
}

void mod_print2(MOD_HEADER mod)
{
	printf("----------------\n");
	printf("ordnum : %d\n",mod.ordnum);
	printf("restart : %d\n",mod.restart);
}

void mod_print_sample(MOD_SAMPLE mod,int i)
{
	printf("----------------\n");
	printf("SAMPLE : %d\n",i);
	printf("name : %.22s\n",mod.name);
	printf("length : %d\n",mod.length);
	printf("finetune : %d\n",mod.finetune);
	printf("volume : %d\n",mod.volume);
	printf("loop start : %d\n",mod.loopstart);
	printf("loop len: %d\n",mod.looplen);
}
