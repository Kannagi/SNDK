#include <stdio.h>
#include <stdlib.h>

#include "vgm.h"

typedef struct
{
	unsigned char pan,env,fdh,fdl,st,lsl,lsh,kon;
	int inst,pitch;

}RICOH;

/*
Pitch 2
volume 1
instrument

PVKI IIII

0xCC
*/

const int debug = 1;

void VGM_Read_RICOH1(VGM vgm,unsigned char *buffer,char *outname,int pcm)
{
	char line[128];
	unsigned char command[64];
	int i = vgm.data+52,l;
	float t;
	t = vgm.totalsample*(1.0f/44100.0f);
	printf("time %.4f s\n",t);

	printf("----------\n");

	int end = vgm.eof;
	if(vgm.gd3 < vgm.eof)
		end = vgm.gd3;

	VGM_Init(&vgm);
	load_option(&vgm);

	//-------------------
	FILE *file2;

	if(debug == 0) file2 = fopen("debug.txt","w");
	FILE *file = fopen(outname,"wb");
	FILE *from;

	init_brr("SAMPLE_PACK",0);

	int delay;

	int cmd,adr,data,wr,port;

	int creg,chreg,schannel;

	creg = 0;
	chreg = 0;
	schannel = 0;

	RICOH ricoh[8] = {0};
	RICOH ricoh_old[8] = {0};
	int write = 0;
	int wait = 0;

	while(i < end)
	{
		cmd  = buffer[i];
		adr  = buffer[i+1];
		data = buffer[i+2];
		i++;

		//printf("CMD %x %x %x\n",cmd,adr,data);

		switch(cmd)
		{
			//RF5C68
			case 0xB0:

				i+=2;

				switch(adr)
				{
					case 0x00: //ENV
						ricoh[schannel].env = data;

						if(debug == 0)
						{
							sprintf(line,"(env:%x)",data);
							fputs(line,file2);
						}
					break;

					case 0x01: //PAN
						ricoh[schannel].pan = data;

						if(debug == 0)
						{
							sprintf(line,"(pan:%x)",data);
							fputs(line,file2);
						}
					break;

					case 0x02: //FDL
						ricoh[schannel].pitch = (ricoh[schannel].pitch&0xFF00) | (data<<0);

						if(debug == 0)
						{
							sprintf(line,"(pl:%d)",data);
							fputs(line,file2);
						}
					break;

					case 0x03: //FDH
						ricoh[schannel].pitch = (ricoh[schannel].pitch&0xFF) | (data<<8);

						if(debug == 0)
						{
							sprintf(line,"(ph:%d)",data);
							fputs(line,file2);
						}
					break;

					case 0x04: //LSL
						ricoh[schannel].inst = (ricoh[schannel].inst&0xFF00FF) | (data<<8);

						if(debug == 0)
						{
							//sprintf(line,"(inst1:%d)",data);
							//fputs(line,file2);
						}
					break;

					case 0x05: //LSH
						ricoh[schannel].inst = (ricoh[schannel].inst&0x00FFFF) | (data<<16);

						if(debug == 0)
						{
							//sprintf(line,"(inst2:%d)",data);
							//fputs(line,file2);
						}
					break;

					case 0x06: //ST
						ricoh[schannel].inst = ( (ricoh[schannel].inst&0xFFFF00) | (data<<0) ) | 0x1000000;

						if(debug == 0)
						{
							sprintf(line,"(inst:%d)",vgm.inst[data]&0x1F);
							fputs(line,file2);
						}
					break;

					case 0x07: //Control Reg
						schannel = data&0x7;

						if(debug == 0)
						{
							sprintf(line,"\nch%d:",schannel);
							fputs(line,file2);
						}
					break;

					case 0x08: //Channel ON/OFF Reg
						chreg = data;
						//sprintf(line,"(k:%x)",chreg);
						//fputs(line,file2);
					break;

					default:
					break;
				}

				if(adr < 9)
				{
					vgm.sizet[adr]+=1;
				}


			break;

			//Delay
			case 0x61:
				vgm.sizet[10]+=1;
				vgm.size+=1;

				command[0] = 0;
				int nsize = 1,inst = 0;

				for(l = 0;l < 8;l++)
				{
					write = 0;
					if(ricoh[l].inst != 0)
					{
						inst = ricoh[l].inst&0xFF;
						write = 1;
						ricoh[l].inst = 0;
					}

					if(ricoh[l].pan != ricoh_old[l].pan)
					{
						write |= 2;
						ricoh_old[l].pan = ricoh[l].pan;
					}

					if(ricoh[l].env != ricoh_old[l].env)
					{
						write |= 2;
						ricoh_old[l].env = ricoh[l].env;
					}


					if(ricoh[l].pitch != ricoh_old[l].pitch)
					{
						write |= 4;
						ricoh_old[l].pitch = ricoh[l].pitch;
					}

					if(write != 0)
					{
						vgm.size+=1;

						command[nsize] = (write<<5) + (vgm.inst[inst]&0x1F);
						//printf("%x,",command[nsize]&0x1F);
						nsize += 1;

						if(write & 0x2)
						{
							int lenv,renv;
							lenv = ricoh[l].env * (ricoh[l].pan&0x0F);
							renv = ricoh[l].env * (ricoh[l].pan>>4);

							command[nsize+0] = lenv >> 5;
							command[nsize+1] = renv >> 5;
							nsize += 2;
							vgm.size+=2;
						}

						if(write & 0x4)
						{
							//int tmp = (float)(ricoh[l].pitch) * 1.01725f;
							int tmp = ricoh[l].pitch<<1;
							command[nsize+0] = tmp;
							command[nsize+1] = tmp>>8;
							nsize += 2;
							vgm.size+=2;
						}

						if(write & 0x01) ricoh[l].kon = 0;


						command[0] |= 1<<l;
					}else
					{
						int tmp = 1<<l;

						if(chreg & tmp)
						{
							if(ricoh[l].kon == 0)
							{
								if(debug == 0)
								{
									sprintf(line,"(koff:%d)",l);
									fputs(line,file2);
								}
								ricoh[l].kon = 1;

								vgm.size+=1;

								command[0] |= 1<<l;
								command[nsize] = 0x3F;
								nsize += 1;

							}
						}
					}
				}

				fwrite(command,1,nsize,file);



				if(debug == 0)
				{
					sprintf(line,"\nWAIT %d\n",adr+(data<<8));
					fputs(line,file2);
				}

				i+=2;

			break;

			case 0x62: //Delay 1/60 second
				printf("error delay 1/60\n");
				exit(0);

			break;

			case 0x63: //Delay 1/50 second
				printf("error delay 1/50\n");
				exit(0);
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
				i+= VGM_data_pcm_ricoh(i,buffer,&vgm,pcm,file);
			break;

			default:
				//printf("cmd  error %d %x\n",i,buffer[i-2]);
				if( (cmd >= 0x70) && (cmd <= 0x7F) )
				{
					printf("error delay 0x7X\n");
					exit(0);
				}else
					i += VGM_cmd_unk(cmd);
				break;
		}

	}


	VGM_Print_size2(&vgm);

	fseek(file, 0x80+0x1E, SEEK_SET);
	fputc(vgm.sizet[10],file);
	fputc(vgm.sizet[10]>>8,file);

	fclose(file);

	if(debug == 0) fclose(file2);

	close_brr();
}
