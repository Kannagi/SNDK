#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdint.h>

#include "KS.h"
#include "it.h"

void it_print_patterns(IT_PATTERNS it,int i)
{
	printf("----------------\n");
	printf("PATTERN : %d\n",i);

	printf("length : %x\n",it.length);
	printf("rows : %x\n",it.rows);
}

void it_print_instruments(IT_INSTRUMENTS it,int i)
{
	printf("----------------\n");
	printf("INSTRUMENT : %d\n",i);

	printf("impi : %.4s\n",it.impi);
	printf("filename : %.13s\n",it.filename);

}

void it_print_instruments_new(IT_INSTRUMENT_NEW it)
{
	printf("nna : %x\n",it.nna);
	printf("dct : %x\n",it.dct);
	printf("dca : %x\n",it.dca);

	printf("fadeout : %x\n",it.fadeout);
	printf("pitch pan  separation : %x\n",it.pps);

	printf("pitch pan center : %d\n",it.ppc);
	printf("global volume : %d\n",it.gbv);
	printf("dfp : %x\n",it.dfp);
	printf("rv : %x\n",it.rv);
	printf("rp : %x\n",it.rp);


	printf("trkvers : %x\n",it.trkvers);
	printf("num_samples : %x\n",it.num_samples);
	printf("padding : %x\n",it.padding);
	printf("name : %.26s\n",it.name);

	printf("ifc : %x\n",it.ifc);
	printf("ifr : %x\n",it.ifr);
	printf("mch : %x\n",it.mch);
	printf("mpr : %x\n",it.mpr);
	printf("midibank : %x\n",it.midibank);

}

void it_print_instruments_old(IT_INSTRUMENT_OLD it)
{
	printf("flg : %x\n",it.flg);
	printf("vls : %x\n",it.vls);
	printf("vle : %x\n",it.vle);
	printf("sls : %x\n",it.sls);
	printf("sle : %x\n",it.sle);

	printf("fadeout : %x\n",it.fadeout);
	printf("nna : %x\n",it.nna);
	printf("dnc : %x\n",it.dnc);
	printf("trkvers : %x\n",it.trkvers);

	printf("name : %.26s\n",it.name);
}

void it_print(IT_HEADER it)
{
	printf("ID_impm: %.4s\n",it.impm);
	printf("Title: %.26s\n",it.title);

	printf("highlight_minor: %x\n",it.highlight_minor);
	printf("highlight_major: %x\n",it.highlight_major);

	printf("ordnum: %x\n",it.ordnum);
	printf("insnum: %x\n",it.insnum);
	printf("smpnum: %x\n",it.smpnum);
	printf("patnum: %x\n",it.patnum);

	printf("cwtv: %x\n",it.cwtv);
	printf("cmwt: %x\n",it.cmwt);
	printf("flags: %x\n",it.flags);
	printf("special: %x\n",it.special);

	printf("global volume: %x\n",it.gv);
	printf("mixing volume: %x\n",it.mv);
	printf("initial speed: %x\n",it.is);
	printf("initial tempo: %x\n",it.it);
	printf("separation: %x\n",it.sep);
	printf("pwd: %x\n",it.pwd);

	printf("msg_length: %x\n",it.msg_length);
	printf("msg_offset: %x\n",it.msg_offset);
	printf("reserved: %x\n",it.reserved);
}

void it_print_sample(IT_SAMPLE it,int i)
{
	printf("----------------\n");
	printf("SAMPLE : %d\n",i);

	printf("gvl : %x\n",it.gvl);
	printf("flag : %x\n",it.flag);
	printf("vol : %x\n",it.vol);

	printf("name : %s\n",it.name);

	printf("cvt : %x\n",it.cvt);
	printf("default pan : %x\n",it.dfp);

	printf("length : %x\n",it.length);
	printf("loop_start : %x\n",it.loop_start);
	printf("loop_end : %x\n",it.loop_end);
	printf("c5speed : %x\n",it.c5speed);

	printf("susloop_start : %x\n",it.susloop_start);
	printf("susloop_end : %x\n",it.susloop_end);
	printf("sample_pointer : %x\n",it.sample_pointer);

	printf("vibrato Speed : %x\n",it.vis);
	printf("vibrato Depth : %x\n",it.vid);
	printf("vibrato Rate: %x\n",it.vir);
	printf("vibrato waveform : %x\n",it.vit);
}

