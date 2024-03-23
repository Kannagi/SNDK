#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

#include "KS.h"


#define PI 3.14159265

#define MAX(a, b) ((a)>(b) ? (a) : (b))

void *safe_malloc(const size_t s)
{
	void *p = malloc(s);
	if(!p)
	{
		fprintf(stderr, "Can't allocate enough memory.\n");
		exit(1);
	}
	return p;
}
static double sinc(const double x)
{
	if(x == 0.0)
		return 1.0;
	else
		return sin(PI * x) / (PI * x);
}

signed short *KS_resample(signed short *samples, int samples_length, int out_length, char type)
{
	double ratio = (double)samples_length / (double)out_length;
	signed short *out = safe_malloc(2 * out_length);

	//printf("Resampling by effective ratio of %f...\n", ratio);
/*
	int pcm = 0,max = 0;

	for(int i=0; i<samples_length; ++i)
	{
		pcm = samples[i];
		if(pcm < 0) pcm = -pcm;
		if(pcm > max)
			max = pcm;
	}

	double volume = 4.0;
	while( ( (int)(max*volume) ) > 32000) volume -= 0.1;

*/

	switch(type) {
	case 'n':								//No interpolation
 		for(int i=0; i<out_length; ++i)
		{
			out[i] = samples[(int)floor(i*ratio)];
		}
		break;
	case 'l':								//Linear interpolation
		for(int i=0; i<out_length; ++i)
		{
			int a = (int)(i*ratio);		//Whole part of index
			double b = i*ratio-a;		//Fractional part of index
			if((a+1)==samples_length)
				out[i] = samples[a];	//This used only for the last sample
			else
				out[i] = (1-b)*samples[a]+b*samples[a+1];
		}
		break;
	case 's':								//Sine interpolation
		for(int i=0; i<out_length; ++i)
		{
			int a = (int)(i*ratio);
			double b = i*ratio-a;
			double c = (1.0-cos(b*PI))/2.0;
			if((a+1)==samples_length)
				out[i] = samples[a];	//This used only for the last sample
			else out[i] = (1-c)*samples[a]+c*samples[a+1];
		}
		break;
	case 'c':										//Cubic interpolation
		for(int i=0; i<out_length; ++i)
		{
			int a = (int)(i*ratio);

			short s0 = (a == 0) ? samples[0] : samples[a-1];
			short s1 = samples[a];
			short s2 = (a+1 >= samples_length) ? samples[samples_length-1] : samples[a+1];
			short s3 = (a+2 >= samples_length) ? samples[samples_length-1] : samples[a+2];

			double a0 = s3-s2-s0+s1;
			double a1 = s0-s1-a0;
			double a2 = s2-s0;
			double b = i*ratio-a;
			double b2 = b*b;
			double b3 = b2*b;
			out[i] = b3*a0 + b2*a1 + b*a2 + s1;
		}
		break;

	case 'b':									// Bandlimited interpolation
		// Antialisaing pre-filtering
		if(ratio > 1.0)
		{
			signed short *samples_antialiased = safe_malloc(2 * samples_length);

			#define FIR_ORDER (15)
			double fir_coefs[FIR_ORDER+1];
			// Compute FIR coefficients
			for(int k=0; k<=FIR_ORDER; ++k)
				fir_coefs[k] = sinc(k/ratio)/ratio;

			// Apply FIR filter to samples
			for(int i=0; i<samples_length; ++i)
			{
				double acc = samples[i] * fir_coefs[0];
				for(int k=FIR_ORDER; k>0; --k)
				{
					acc += fir_coefs[k] * ((i+k < samples_length) ? samples[i+k] : samples[samples_length-1]);
					acc += fir_coefs[k] * ((i-k >= 0) ? samples[i-k] : samples[0]);
				}
				samples_antialiased[i] = (signed short)(acc);
			}

			free(samples);
			samples = samples_antialiased;
		}
		// Actual resampling using sinc interpolation
		for(int i=0; i<out_length; ++i)
		{
			double a = i*ratio;
			double acc = 0.0;
			for(int j=(int)a-FIR_ORDER; j<=(int)a+FIR_ORDER; ++j)
			{
				signed short sample;
				if(j >=0)
					if(j < samples_length)
						sample = samples[j];
					else
						sample = samples[samples_length-1];
				else
					sample = samples[0];

				acc += sample*sinc(a-j);
			}
			out[i] = (signed short)acc;
		}
		break;

	default :
		fprintf(stderr, "\nError : A valid interpolation algorithm must be chosen !\n");
		//print_instructions();
	}
	// No longer need the non-resampled version of the sample
	free(samples);
	return out;
}

signed short* KS_resample16bits(unsigned char *data,int len,int type)
{
	int i;
	if(type == 1) return (signed short*)data;
	if(data == NULL) return NULL;

	unsigned short *sdata = malloc(len*sizeof(signed short));
	int sample;

	for(i = 0;i < len;i++)
	{
		if(data[i] <= 0x80)
		{
			sample = 0x10000 - (0x8000 - (int)( (data[i]<<8) ));
		}else
		{
			sample = (int)( ((data[i]-0x80)<<8) );
		}


		sdata[i] = sample;
	}

	free(data);
	return (signed short*)sdata;
}

int KS_compress(unsigned char *data,int len,int type,int lz)
{
	int i,l;

	unsigned short *sdata = (void*)data;
	unsigned int sample;
	if(lz <= 0) lz = 1;
	len = len/(lz);

	if(type == 1)
	{
		len = len/2;
		for(i = 0;i < len;i++)
		{
			l = i*lz;

			sample = sdata[l];
			sdata[i] = sample;
		}

	}else
	{
		for(i = 0;i < len;i++)
		{
			l = i*lz;
			sample = data[l];
			data[i] = sample;
		}
	}
	return len;
}
