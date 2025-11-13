#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>

static uint8_t sc16_buffer[0x10000];

static uint16_t sc16_buffer_hash1[0x10000];
static uint16_t sc16_buffer_hash2[0x10000];
static uint16_t sc16_buffer_hash4[0x10000];

static uint8_t sc16_map[0x10000];

static uint64_t sc16_map4[0x2000];
static uint32_t sc16_map2[0x4000];
static uint16_t sc16_map1[0x8000];


static uint16_t sc16_buffer_data1[0x100];
static uint32_t sc16_buffer_data2[0x100];
static uint64_t sc16_buffer_data4[0x100];

static int count4;
static int count2;
static int count1;

#define MAX_INDEX 250

uint16_t sc16_map_4(uint64_t item)
{
	for(int i = 0;i < count4;i++)
	{
		if(sc16_map4[i] == item)
		{
			return i;
		}
	}

	sc16_map4[count4] = item;
	count4++;

	return count4-1;
}

uint16_t sc16_map_2(uint32_t item)
{
	for(int i = 0;i < count2;i++)
	{
		if(sc16_map2[i] == item)
		{
			return i;
		}
	}


	sc16_map2[count2] = item;
	count2++;

	return count2-1;
}

uint16_t sc16_map_1(uint16_t item)
{
	for(int i = 0;i < count1;i++)
	{
		if(sc16_map1[i] == item)
		{
			return i;
		}
	}

	sc16_map1[count1] = item;
	count1++;

	return count1-1;
}

void *sc16(void *data,int *size)
{
	int fsize = *size;

	if(fsize >= 0x10000)
		return data;

	uint16_t *sdata = data;

	memset(sc16_buffer_hash1,0,0x20000);
	memset(sc16_buffer_hash2,0,0x20000);
	memset(sc16_buffer_hash4,0,0x20000);
	memset(sc16_map,0,0x10000);

	fsize = fsize>>1;

	uint16_t imap,sindex = 0;
	int bloc8,bloc4,bloc2,blocr = 0;
	bloc8 = 0;
	bloc4 = 0;
	bloc2 = 0;

	count4 = 0;
	count2 = 0;
	count1 = 0;

	//--------------------RLE-----------------
	uint16_t begin = 0;


	uint64_t old_index = ((uint64_t)sdata[0] | ((uint64_t)sdata[0+1] << 16) | ((uint64_t)sdata[0+2] << 32) | ((uint64_t)sdata[0+3] << 48 ) );
	int rle = 0,dif;

	for(int i = 4;i < fsize;i+=4)
	{
		uint64_t index = ((uint64_t)sdata[i] | ((uint64_t)sdata[i+1] << 16) | ((uint64_t)sdata[i+2] << 32) | ((uint64_t)sdata[i+3] << 48 ) );

		if(index == old_index)
		{
			if(rle == 0)
				begin = i-4;
			rle++;
		}
		else
		{
			if(rle > 4)
			{

				blocr++;
				blocr++;

				blocr+=8;
				dif = (i-4) - begin;
				for(int l = begin;l < (i-4);l+=4)
				{
					sc16_map[l+0] = 5+(dif&0xF);
					sc16_map[l+1] = 5+( (dif>>4)&0xF );
					sc16_map[l+2] = 5+( (dif>>8)&0xF );
					sc16_map[l+3] = 5+( (dif>>12)&0xF );
				}
			}

			rle = 0;
		}
		old_index = index;
	}

	if(rle > 4)
	{
		blocr++;
		blocr++;

		blocr+=8;
		dif = fsize - begin;

		for(int l = begin;l < fsize;l+=4)
		{
			sc16_map[l+0] = 5+(dif&0xF);
			sc16_map[l+1] = 5+( (dif>>4)&0xF );
			sc16_map[l+2] = 5+( (dif>>8)&0xF );
			sc16_map[l+3] = 5+( (dif>>12)&0xF );
		}
	}

	//---------------------------
	const char *tag ="sc16";
	const short nbloc = 1;
	memcpy(&sc16_buffer[0],tag,4);
	memcpy(&sc16_buffer[4],&nbloc,2);
	sindex = 12;

	//--------------------BLOC8-----------------

	int imax = 0;
	int tpal = 0;
	uint16_t pal1,pal2,pal3;
	uint16_t idata = 0;

	for(int i = 0;i < fsize;i+=4)
	{
		if(sc16_map[i] == 0)
		{
			uint64_t bdata = (uint64_t)sdata[i] | ((uint64_t)sdata[i+1] << 16) | ((uint64_t)sdata[i+2] << 32) | ((uint64_t)sdata[i+3] << 48 );
			uint16_t index = sc16_map_4(bdata);
			if(imax < MAX_INDEX)
			{
				sc16_buffer_hash4[index]++;
				if(sc16_buffer_hash4[index] == 2)
				{
					memcpy(&sc16_buffer[sindex],&bdata,8);
					sindex+=8;
					tpal++;
					imax++;
					bloc8++;

					sc16_buffer_data4[idata] = bdata;
					idata++;
				}
			}
		}
	}

	pal1 = tpal;
	sc16_buffer[9] = pal1;

	for(int i = 0;i < fsize;i+=4)
	{
		if(sc16_map[i] == 0)
		{
			uint16_t index = sc16_map_4((uint64_t)sdata[i] | ((uint64_t)sdata[i+1] << 16) | ((uint64_t)sdata[i+2] << 32) | ((uint64_t)sdata[i+3] << 48 ) );

			imap = sc16_buffer_hash4[index];
			if(imap > 1)
			{
				sc16_map[i+0] = 4;
				sc16_map[i+1] = 4;
				sc16_map[i+2] = 4;
				sc16_map[i+3] = 4;
			}
		}
	}

	//------------------BLOC4-------------------
	idata = 0;
	for(int i = 0;i < fsize;i+=2)
	{
		if(sc16_map[i] == 0)
		{
			uint32_t bdata = (uint32_t)sdata[i] | ((uint32_t)sdata[i+1] << 16);
			uint16_t index = sc16_map_2(bdata );
			if(imax < MAX_INDEX)
			{
				sc16_buffer_hash2[index]++;
				if(sc16_buffer_hash2[index] == 2)
				{
					memcpy(&sc16_buffer[sindex],&bdata,4);
					sindex+=4;
					tpal++;
					imax++;
					bloc4++;

					sc16_buffer_data2[idata] = bdata;
					idata++;
				}
			}
		}
	}

	pal2 = tpal-pal1;
	sc16_buffer[10] = pal2;

	for(int i = 0;i < fsize;i+=2)
	{
		if(sc16_map[i] == 0)
		{
			uint16_t index = sc16_map_2((uint32_t)sdata[i] | ((uint32_t)sdata[i+1] << 16) );

			imap = sc16_buffer_hash2[index];
			if(imap > 1)
			{
				sc16_map[i+0] = 2;
				sc16_map[i+1] = 2;
			}
		}

	}

	//--------------BLOC2-------------
	idata = 0;
	for(int i = 0;i < fsize;i++)
	{
		if(sc16_map[i] == 0)
		{
			uint16_t index = sc16_map_1(sdata[i]);
			if(imax < MAX_INDEX)
			{
				sc16_buffer_hash1[index]++;
				if(sc16_buffer_hash1[index] == 2)
				{
					memcpy(&sc16_buffer[sindex],&sdata[i],2);
					sindex+=2;
					tpal++;
					imax++;
					bloc2++;

					sc16_buffer_data1[idata] = sdata[i];
					idata++;
				}
			}
		}
	}

	pal3 = tpal-pal1-pal2;
	sc16_buffer[11] = pal3;

	for(int i = 0;i < fsize;i++)
	{
		if(sc16_map[i] == 0)
		{
			uint16_t index = sc16_map_1(sdata[i]);

			imap = sc16_buffer_hash1[index];
			if(imap > 1)
			{
				sc16_map[i+0] = 1;
			}
		}
	}

	//--------------------WRITE---------------------
	int bloc = 0,bloc0 = 0;
	uint16_t literal = 0;
	uint16_t command = 0;

	for(int i = 0;i < fsize;i++)
	{
		uint8_t map = sc16_map[i];


		if(map == 0)
		{
			sc16_buffer_hash1[literal] = sdata[i];
			literal++;
		}else
		{
			if(literal != 0)
			{

				//printf("lit %d\n",literal);
				if(literal == 4)
				{
					command++;
					sc16_buffer[sindex] = 0xFE;
					sindex++;

					memcpy(&sc16_buffer[sindex],&sc16_buffer_hash1[0],8);
					sindex+=8;

					bloc0+=9;
				}
				else
				if(literal == 2)
				{
					command++;
					sc16_buffer[sindex] = 0xFD;
					sindex++;

					memcpy(&sc16_buffer[sindex],&sc16_buffer_hash1[0],4);
					sindex+=4;

					bloc0+=5;
				}
				else
				if(literal == 1)
				{
					command++;
					sc16_buffer[sindex] = 0xFC;
					sindex++;

					memcpy(&sc16_buffer[sindex],&sc16_buffer_hash1[0],2);
					sindex+=2;

					bloc0+=3;
				}
				else
				{
					int ny = 1+(literal>>8);
					int tmp;

					for(int y = 0;y < ny;y++)
					{
						sc16_buffer[sindex] = 0xFF;
						sindex++;
						command++;

						if(y == (ny-1))
							tmp = literal%0xFF;
						else
							tmp = 0xFF;

						sc16_buffer[sindex] = tmp;
						sindex++;

						memcpy(&sc16_buffer[sindex],&sc16_buffer_hash1[y*0xFF],tmp*2);
						sindex+=tmp*2;
					}

				}

				literal = 0;
			}
		}

		if(map == 1)
		{
			command++;
			uint16_t index = 0;
			uint16_t pdata = sdata[i];

			for(int l = 0;l < pal3;l++)
			{
				if( sc16_buffer_data1[l] == pdata)
				{
					index = l;
					break;
				}
			}
			sc16_buffer[sindex] = index+pal1+pal2;
			sindex++;
			bloc++;
		}

		if(map == 2)
		{
			command++;
			uint16_t index = 0;
			uint32_t pdata = ((uint32_t)sdata[i] | ((uint32_t)sdata[i+1] << 16) );

			for(int l = 0;l < pal2;l++)
			{
				if( sc16_buffer_data2[l] == pdata)
				{
					index = l;
					break;
				}
			}
			sc16_buffer[sindex] = index+pal1;
			sindex++;
			bloc++;
			i+=1;
		}

		if(map == 4)
		{
			command++;
			uint16_t index = 0;
			uint64_t pdata = ((uint64_t)sdata[i] | ((uint64_t)sdata[i+1] << 16) | ((uint64_t)sdata[i+2] << 32) | ((uint64_t)sdata[i+3] << 48 ) );

			for(int l = 0;l < pal1;l++)
			{
				if( sc16_buffer_data4[l] == pdata)
				{

					index = l;
					break;
				}
			}
			//printf("index4 : %d\n",index);
			sc16_buffer[sindex] = index;
			sindex++;
			bloc++;
			i+=3;
		}

		if(map >= 5)
		{
			uint64_t bdata = (uint64_t)sdata[i] | ((uint64_t)sdata[i+1] << 16) | ((uint64_t)sdata[i+2] << 32) | ((uint64_t)sdata[i+3] << 48 );

			int lenght = sc16_map[i+0]-5;
			lenght |= (sc16_map[i+1]-5)<<4;
			lenght |= (sc16_map[i+2]-5)<<8;
			lenght |= (sc16_map[i+3]-5)<<12;

			int lenght8 = lenght>>2;

			int ny = 1+(lenght8>>8);
			int tmp;

			for(int y = 0;y < ny;y++)
			{
				sc16_buffer[sindex] = 0xFB;
				sindex++;

				command++;

				if(y == (ny-1))
					tmp = lenght8%0xFF;
				else
					tmp = 0xFF;

				//printf("%d\n",tmp);

				sc16_buffer[sindex] = tmp;
				sindex++;

				memcpy(&sc16_buffer[sindex],&bdata,8);
				sindex+=8;
				if(lenght8 > 0) lenght8--;
			}

			i+=lenght+3;
		}

	}

	//--------------------WRITE RAW end---------------------
	if(literal != 0)
	{

		int ny = 1+(literal>>8);
		int tmp;

		for(int y = 0;y < ny;y++)
		{
			sc16_buffer[sindex] = 0xFF;
			sindex++;

			command++;

			if(y == (ny-1))
				tmp = literal%0xFF;
			else
				tmp = 0xFF;

			sc16_buffer[sindex] = tmp;
			sindex++;

			memcpy(&sc16_buffer[sindex],&sc16_buffer_hash1[y*0xFF],tmp*2);
			sindex+=tmp*2;
		}


	}
	//-------------------------

	//printf("%d / %d  / %d / %d / %d\n",bloc8,bloc4,bloc2,bloc0 , bloc);

	float percent = (float)sindex/(float)(*size);
	printf("Compressed %d bytes into %d bytes ==> %.2f%% \n",*size,sindex,percent*100);

	//-----------------
	*size = sindex;
	//printf("%d Bytes\n",sindex);

	sindex -= 8;
	//memcpy(&sc16_buffer[6],&sindex,2);
	memcpy(&sc16_buffer[6],&command,2);


	return sc16_buffer;
}
