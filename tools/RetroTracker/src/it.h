
#ifndef _IT_SOUND_FORMAT___
#define _IT_SOUND_FORMAT___


typedef struct
{
	uint16_t length,rows;
	uint32_t x;
	uint8_t *data;

}IT_PATTERNS;

typedef struct
{
	char imps[4], filename[13];
	uint8_t gvl, flag, vol;
	char name[26];
	uint8_t cvt, dfp;
	uint32_t length, loop_start, loop_end, c5speed;
	uint32_t susloop_start, susloop_end, sample_pointer;
	uint8_t vis, vid, vir, vit;

	char *data;
}IT_SAMPLE;

typedef struct
{
	uint8_t note;
	uint8_t sample;
}it_notetrans;

typedef struct
{
	uint8_t flags, num_nodes, loop_start, loop_end;
	uint8_t susloop_start, susloop_end;
	struct
	{
		int8_t value; // signed (-32 -> 32 for pan and pitch; 0 -> 64 for vol and filter)
		uint16_t tick;
	}nodes[25];
	uint8_t padding;
}it_envelope;

typedef struct
{
	uint8_t flg, vls, vle, sls, sle;
	uint8_t xx[2];
	uint16_t fadeout;
	uint8_t nna, dnc;
	uint16_t trkvers;
	uint8_t nos;
	uint8_t x;
	char name[26];
	uint8_t xxxxxx[6];
	it_notetrans notetrans[120];
	uint8_t vol_env[200];
	uint8_t node_points[50];
}IT_INSTRUMENT_OLD;

typedef struct
{
	uint8_t nna, dct, dca;
	uint16_t fadeout;
	int8_t pps; // signed!
	uint8_t ppc, gbv, dfp, rv, rp;
	uint16_t trkvers;
	uint8_t num_samples, padding;
	char name[26];
	uint8_t ifc, ifr, mch, mpr;
	uint16_t midibank;
	it_notetrans notetrans[120];
	it_envelope vol_env, pan_env, pitch_env;

}IT_INSTRUMENT_NEW;

typedef struct
{
	char impi[4], filename[13];

	IT_INSTRUMENT_NEW n;
	IT_INSTRUMENT_OLD o;

}IT_INSTRUMENTS;

typedef struct
{
	char impm[4], title[26];
	uint8_t highlight_minor, highlight_major;
	uint16_t ordnum, insnum, smpnum, patnum;
	uint16_t cwtv, cmwt, flags, special;
	uint8_t gv, mv, is, it, sep, pwd;
	uint16_t msg_length;
	uint32_t msg_offset, reserved;
	uint8_t chan_pan[64], chan_vol[64];

	char ord_table[256];

	int insOff[256];
	int smpOff[256];
	int patOff[256];

}IT_HEADER;


void it_convert_pattern(KS_FORMAT *ks,FILE *fichier,int n,int begin);
int it_relative(int spd);
int it_convert_effect(int effect);

void it_print_patterns(IT_PATTERNS it,int i);
void it_print_instruments(IT_INSTRUMENTS it,int i);
void it_print_instruments_new(IT_INSTRUMENT_NEW it);
void it_print_instruments_old(IT_INSTRUMENT_OLD it);
void it_print(IT_HEADER it);
void it_print_sample(IT_SAMPLE it,int i);

#endif
