#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "KS.h"
#include "xm.h"

void xm_print_instruments(XM_HEADER xm,int i)
{
	printf("-------------------\n");
	printf("INSTRUMENTS %d size : %d\n",i+1,xm.instruments[i]->size);
	printf("INSTRUMENTS %d name : %s\n",i+1,xm.instruments[i]->name);
	printf("INSTRUMENTS %d type : %d\n",i+1,xm.instruments[i]->type);
	printf("INSTRUMENTS %d Nsamples : %d\n",i+1,xm.instruments[i]->Nsamples);
}

void xm_print_instruments_ext(XM_HEADER xm,int i)
{
	printf("-------------------\n");
	printf("INSTRUMENTS_EXT %d size : %d\n",i+1,xm.instruments[i]->size);
	printf("INSTRUMENTS_EXT %d name : %s\n",i+1,xm.instruments[i]->name);
	printf("INSTRUMENTS_EXT %d type : %d\n",i+1,xm.instruments[i]->type);
	printf("INSTRUMENTS_EXT %d Nsamples : %d\n",i+1,xm.instruments[i]->Nsamples);
}


void xm_print_samples(XM_SAMPLE xm_sample,int i)
{
	printf("SAMPLE %d length : %d\n",i,xm_sample.length);
	printf("SAMPLE %d loop_start : %d\n",i,xm_sample.loop_start);
	printf("SAMPLE %d loop_length : %d\n",i,xm_sample.loop_length);
	printf("SAMPLE %d Volume : %d\n",i,xm_sample.Volume);
	printf("SAMPLE %d Finetune : %d\n",i,xm_sample.Finetune);
	printf("SAMPLE %d Type : %d\n",i,xm_sample.type);
	printf("SAMPLE %d Panning : %d\n",i,xm_sample.Panning);
	printf("SAMPLE %d Relative : %d\n",i,xm_sample.Relative);
	printf("SAMPLE %d Reserved : %d\n",i,xm_sample.Reserved);
	printf("SAMPLE %d name : %.20s\n",i,xm_sample.name);
}

void xm_print_patterns(XM_HEADER xm,int i)
{
	printf("-------------------\n");
	printf("PATTERNS %d length : %d\n",i,xm.patterns[i]->header_length);
	printf("PATTERNS %d type : %d\n",i,xm.patterns[i]->type);
	printf("PATTERNS %d Nrowspattern : %d\n",i,xm.patterns[i]->Nrowspattern);
	printf("PATTERNS %d size : %d\n",i,xm.patterns[i]->size);
}

void xm_print(XM_HEADER xm)
{
	printf("ID_text: %.16s\n",xm.ID_text);
	printf("Module_name : %.18s\n",xm.Module_name);
	printf("x : $%x\n",xm.x);
	printf("Tracker_name : %.18s\n",xm.Tracker_name);

	printf("Version_number : $%x\n",xm.Version_number);
	printf("Header_size : $%x\n",xm.Header_size);

	printf("Song_length : %d\n",xm.Song_length);
	printf("Restart_position : %d\n",xm.Restart_position);
	printf("Nchannels : %d\n",xm.Nchannels);
	printf("Npatterns : %d\n",xm.Npatterns);
	printf("Ninstruments : %d\n",xm.Ninstruments);
	printf("Flags : $%x\n",xm.Flags);
	printf("tempo : %d\n",xm.tempo);
	printf("BPM : %d\n",xm.BPM);
}

