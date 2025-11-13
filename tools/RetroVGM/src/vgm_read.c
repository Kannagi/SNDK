#include <stdio.h>
#include <stdlib.h>

#include "vgm.h"

void VGM_Read_YM(VGM vgm,unsigned char *buffer,char *outname,int pcm)
{
	int i = vgm.data+52;
	float t;
	t = vgm.totalsample*(1.0f/44100.0f);
	printf("time %.4f s\n",t);

	printf("----------\n");

	int end = vgm.eof;
	if(vgm.gd3 < vgm.eof)
		end = vgm.gd3;

	VGM_Init(&vgm);

	//-------------------
	FILE *file = fopen(outname,"wb");
	FILE *from;
	if(pcm >= 1)
	{
		from = fopen("052-v1.bin","wb");

		int nsize = pcm * 0x100000;

		for (long l = 0; l < nsize; l++)
			fputc(0,from);

		rewind(from);
	}

	int delay;

	int cmd,adr,data,wr,port;

	while(i < end)
	{
		cmd  = buffer[i];
		adr  = buffer[i+1];
		data = buffer[i+2];
		i++;

		//printf("CMD %x %x %x\n",cmd,adr,data);

		switch(cmd)
		{
			//YM2610 Port 0
			case 0x58:

				if(adr < 0x10)
				{
					vgm.sizet[2]+=2;
				}else
				{
					if(adr < 0x20)
					{
						vgm.sizet[1]+=2;
					}else
					{
						if(adr < 0x30)
						{
							vgm.sizet[3]+=2;
						}else
						{
							vgm.sizet[4]+=2;
						}
					}

				}

				wr = 0;
				port = vgm.port0[adr&0xFF];

				if(port != data)
				{
					vgm.port0[adr&0xFF] = data;
					wr = 1;
				}

				//SSG
				if(port == 0x07) wr = 1;
				if(port == 0x08) wr = 1;
				if(port == 0x09) wr = 1;
				if(port == 0x0A) wr = 1;

				//ADPCM B
				if(port == 0x10) wr = 1;
				if(port == 0x1C) wr = 1;

				//FM
				if(port == 0x22) wr = 1;
				if(port == 0x28) wr = 1;

				if(wr == 1)
				{
					fputc(0x01,file);
					fputc(adr,file);
					fputc(data,file);
					vgm.size+=3;
				}
				i+=2;
			break;

			//YM2610 Port 1
			case 0x59:


				wr = 0;

				if(adr < 0x30) //ADPCM-A
				{
					vgm.sizet[0]+=2;
				}else //FM
				{
					vgm.sizet[4]+=2;
				}

				i+=2;

				port = vgm.port1[adr&0xFF];

				if(port != data)
				{
					vgm.port1[adr&0xFF] = data;
					wr = 1;
				}

				if(port == 0) wr = 1;
				if(port == 1) wr = 0;

				if(wr == 1)
				{
					fputc(0x02,file);
					fputc(adr,file);
					fputc(data,file);
					vgm.size+=3;
				}

			break;

			//Delay
			case 0x61:
				delay = buffer[i] + (buffer[i+1]<<8);
				VGM_delay(&vgm,file,delay);

				i+=2;

			break;

			case 0x62: //Delay 1/60 second
				VGM_delay(&vgm,file,735);
			break;

			case 0x63: //Delay 1/50 second
				VGM_delay(&vgm,file,882);
			break;


			//Delay
			case 0x64:
				printf("cmd wait error\n");
				i+=2;
			break;

			//END
			case 0x66:
				printf("cmd end\n");
			break;

			//DATA PCM
			case 0x67:
				i+= VGM_data_pcm(i,buffer,&vgm,pcm);
				printf("offset : %x\n",i);
			break;

			default:
				//printf("cmd  error %d %x\n",i,buffer[i-2]);
				if( (cmd >= 0x70) && (cmd <= 0x7F) )
				{
					VGM_delay(&vgm,file, (cmd&0xF) );
				}else
					i += VGM_cmd_unk(cmd);
				break;
		}

	}

	fputc(0x00,file);
	vgm.size+=1;

	VGM_Print_size(&vgm);

	fclose(file);

	if(pcm >= 1)
		fclose(from);

}

