#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "KS.h"

void wavinfo(WAV wav);

void output_filename(char *adresse,char *schaine)
{
    int l = 0;
    int i = 0;
    while(adresse[i] != 0 && adresse[i] != '.' )
    {
        schaine[l] = adresse[i];
        l++;

        if(adresse[i] == '/' || adresse[i] == '\\') l = 0;
        i++;
    }
    schaine[l] = 0;
}

static FILE *filebrr = NULL;

void init_brr(char * str,int mode)
{
	char ostr[256];
	sprintf(ostr,"%s.brr",str);

	if(mode == 0)
		filebrr = fopen(ostr,"wb");
	else
	{
		filebrr = fopen("demo.smc","rb+");
		fseek(filebrr,0x8000*4,SEEK_SET);
	}

}

void offset_brr(int offset)
{
	if(filebrr != NULL)
		fseek(filebrr,offset,SEEK_SET);
}

void close_brr()
{
	if(filebrr != NULL)
		fclose(filebrr);
}

int savebrr( char *adresse,unsigned char *data,int len,int type,int dec,int begin,int out)
{
	int end,octet;
    int hbrr;
    int pcm[16];

    int l,i = begin;
    int sht,max = 0;
    int size = 0;

    //unsigned short *sdata =data;



    while(i < len)
    {
    	//printf("block : %d\n",i/16);
        end = 0;
        size +=9;
        max = 0;

        for(l = 0;l < 16;l++)
        {
        	pcm[l] = 0;
			if(type == 1)
			{

				pcm[l] = data[i+0] + (data[i+1]<<8);
				i += 2+dec+dec;
			}
			else
			{
				if(data[i] <= 0x80)
				{
					pcm[l] = 0x10000 - (0x8000 - (int)( (data[i]<<8) ));
				}else
				{
					pcm[l] = (int)( ((data[i]-0x80)<<8) );
				}
				i += 1+dec;
			}

			if(pcm[l] < 0x8000)
            {
                if(pcm[l] > max) max = pcm[l];
            }else
            {
                if(0x10000-pcm[l] > max) max = 0x10000-pcm[l];
            }

            if(i+1 >= len)
			{
				end = 1;

				break;
			}

			//printf("%d\n",pcm[l]);
        }
        for(l = l;l < 16;l++) pcm[l] = 0;

        hbrr = 0x00;

        if(max >= 0x0008) hbrr = 0x10;
        if(max >= 0x0010) hbrr = 0x20;
        if(max >= 0x0020) hbrr = 0x30;
        if(max >= 0x0040) hbrr = 0x40;
        if(max >= 0x0080) hbrr = 0x50;
        if(max >= 0x0100) hbrr = 0x60;
        if(max >= 0x0200) hbrr = 0x70;
        if(max >= 0x0400) hbrr = 0x80;
        if(max >= 0x0800) hbrr = 0x90;
        if(max >= 0x1000) hbrr = 0xA0;
        if(max >= 0x2000) hbrr = 0xB0;
        if(max >= 0x4000) hbrr = 0xC0;



        sht = hbrr >> 4;
        if(i >= len - 15) end = 1;

        if(end == 1) hbrr += 0x01;

        fputc(hbrr+out,filebrr);

        int tmppcm;
        for(l = 0;l < 16;l+=2)
        {
        	tmppcm = pcm[l+0];
            if(tmppcm < 0x8000)
            {
                octet = (tmppcm >> sht)<<4;
            }else
            {
                tmppcm = 0x10000-tmppcm;
                tmppcm = tmppcm >> sht;

                if(0x10-tmppcm == 0x10)
					octet = 0;
				else
					octet = (0x10-tmppcm)<<4;
            }

            tmppcm = pcm[l+1];
            if(tmppcm < 0x8000)
            {
                octet += tmppcm >> sht;
            }else
            {
                tmppcm = 0x10000-tmppcm;
                tmppcm = tmppcm >> sht;

				if(0x10-tmppcm != 0x10)
					octet += 0x10-tmppcm;
            }


            fputc(octet,filebrr);
        }
    }


    return size;
}

void savewav( char *adresse,unsigned char *data,int len,int type,int frq)
{
    FILE *file;

    file = fopen(adresse,"wb");
    if(file == NULL) return;

    WAV wav;
    strcpy(wav.FileTypeBlocID,"RIFF");
    strcpy(wav.FileFormatID,"WAVE");
    strcpy(wav.FormatBlocID,"fmt ");
    strcpy(wav.DataBlocID,"data");
    wav.size = len + 0x24;
    wav.blocsize = 0x10;
    wav.format = 0x01;
    wav.ncanaux = 0x01;
    wav.frequence = frq;
    wav.BytePerSec = frq<<type;
    wav.BytePerBloc = 0x01+type;
    wav.BitsPerSample = 0x08<<type;
    wav.DataSize = len;

    fwrite(&wav , 1, 0x28+4,file);
    fwrite(data , 1, len,file);

    fclose(file);
}

int loadwav(char *address,WAV *wav)
{
    FILE *file;

    file = fopen(address,"rb");
    if(file == NULL) return 0;

    fread(wav , 1, 0x28+4,file);

    unsigned char *data;
    data = malloc(wav->DataSize);

    fread(data , 1, wav->DataSize,file);
    wav->data = data;
    //wavinfo(*wav);
    wav->BytePerBloc--;

    fclose(file);

    return 1;
}

void wavinfo(WAV wav)
{
    printf("File Type : %c%c%c%c \n",wav.FileTypeBlocID[0],wav.FileTypeBlocID[1],wav.FileTypeBlocID[2],wav.FileTypeBlocID[3]);

    printf("Size : %d bytes \n",wav.size);

    printf("File Format : %c%c%c%c \n",wav.FileFormatID[0],wav.FileFormatID[1],wav.FileFormatID[2],wav.FileFormatID[3]);

    printf("File Bloc : %c%c%c \n",wav.FormatBlocID[0],wav.FormatBlocID[1],wav.FormatBlocID[2]);

    printf("Bloc Size : %d \n",wav.blocsize);

    printf("Format : %d \n",wav.format);

    printf("Channel : %d \n",wav.ncanaux);

    printf("Frequence : %d Hz \n",wav.frequence);

    printf("Byte per Sec : %d bytes \n",wav.BytePerSec);

    printf("Byte per Bloc : %d bytes \n",wav.BytePerBloc);

    printf("Byte per Sample : %d bytes \n",wav.BitsPerSample);

    printf("Data Bloc ID : %c%c%c%c \n",wav.DataBlocID[0],wav.DataBlocID[1],wav.DataBlocID[2],wav.DataBlocID[3]);

    printf("Data Size : %d bytes \n",wav.DataSize);




}

int savepcm5b( char *adresse,unsigned char *data,int len,int type,int dec,int begin,int out)
{
    FILE *file = NULL;
    if(out == 0)
		file = fopen(adresse,"wb");
	else
	{
		file = fopen("music.smc","rb+");
		fseek(file,(0x8000*2)+out-1,SEEK_SET);
	}
    if(file == NULL) return 0;

    int pcm[32];

    int l,i = begin;
    int size = 0;

	for(l = 0;l < 32;l++)
		pcm[l] = 0;

	l = 0;
	if( (type == 1) && (len > 64) )
		dec++;

	if( (type != 1) && (len > 32) )
		dec++;

    while(i < len)
    {
		if(type == 1)
		{
			pcm[l] = data[i+0] + (data[i+1]<<8);
			i += 2+dec+dec;
		}
		else
		{
			if(data[i] <= 0x80)
			{
				pcm[l] = 0x10000 - (0x8000 - (int)( (data[i]<<8) ));
			}else
			{
				pcm[l] = (int)( ((data[i]-0x80)<<8) );
			}
			i += 1+dec;
		}

		if(pcm[l] >= 0x8000)
		{
			pcm[l] = 0x10000-pcm[l];
			pcm[l] = 0;
		}

		pcm[l] = pcm[l]>>10;

		if(i+1 >= len)
		{
			break;
		}

		size++;
		l++;
		if(l >= 32)
		{
			break;
		}


    }

    for(l = 0;l < 32;l++)
		fputc(pcm[l],file);

    fclose(file);

    return size;
}
