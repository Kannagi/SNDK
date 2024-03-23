
#ifndef _S3M_SOUND_FORMAT___
#define _S3M_SOUND_FORMAT___



typedef struct
{
	char type;
	char filename[12];

	uint8_t ptrDataH;
	uint16_t ptrDataL;
	uint32_t length,loopStart,loopEnd;

	uint8_t volume,reserved,pack,flags;
	uint32_t c2spd;

	char internal[12];
	char title[28];
	char sig[4];


}S3M_INSTRUMENT;

typedef struct
{
	char name[28];
	uint8_t sig,type;
	uint16_t reserved,orderCount,instrumentCount,patternPtrCount;
	uint16_t flags,trackerVersion,sampleType;

	char sig2[4];

	uint8_t globalVolume,initialSpeed,initialTempo,masterVolume;
	uint8_t ultraClickRemoval,defaultPan;
	uint8_t reserved2[8];

	uint16_t ptrSpecial;
	uint8_t channelSettings[32];

	uint8_t *orderList;
	uint16_t *ptrInstruments,*ptrPatterns;
}S3M_HEADER;

void S3M_XOR_HEADER(S3M_HEADER *s3m);
void s3m_resample(unsigned char *data,int len,int type);

void s3m_print(S3M_HEADER s3m);
void s3m_print_instrument(S3M_INSTRUMENT s3m,int i);
int s3m_relative(int spd);
int s3m_convert_effect(int effect);
#endif
