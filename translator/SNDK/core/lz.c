
void SNDK_LZ_VRAM( uint16 nlabel)
{
	 uint16 adr,adrh;
	 uint16 buf1,buf2,buf3,buf4;
	 uint16 index,pal1,pal2,pal3;
	 uint16 opal1,opal2,opal3,tmp,tmph,i,pal12;
	
	
	nlabel = nlabel<<3;
	idx = nlabel + &SNDK_LOAD();
	
	adr = [0x820000,idx];
	idx += 2;
	
	adrh = [0x820000,idx];
	tmph = acc;
	idx += 2;
	
	VMADD = [0x820000,idx];
	
	
	
	adr += 6;
	
	
	
	idy = @adr;
	adr += 3;
	
	
	pal1 = @adr;
	adr += 1;

	pal2 = @adr;
	adr += 1;

	pal3 = @adr;
	adr += 1;
	
	pal1 &= 0xFF;
	pal2 &= 0xFF;
	pal3 &= 0xFF	;
	pal12 = 0;
	
	
	pal12 = pal1+pal2;
	
	
	
	i = 0;

	opal1 = i + adr;
	acc = pal1 << 3;
	i += acc;
	
	opal2 = i + adr;
	acc = pal2 << 2;
	i += acc;

	opal3 = i + adr;
	acc = pal3 << 1;
	i += acc;

	adr += i;
	
	index = 0;
		
	
	
	do
	{
		index = @adr;
		
		adr += 1;
		

		if( index >= 0xFB)
		{
			jump SNDK_LZ_JBEG();
		}
		
		
		 uint16 type;
		type = 0;
		
		if( index >= pal1)
		{
			type += 1;
		}
		
		if( index >= pal12)
		{
			type += 1;
		}
		
		if( type == 0)
		{
			
			acc = index << 3;
			tmp = acc + opal1;

			VMDATA = @tmp;
			tmp += 2;
			VMDATA = @tmp;
			tmp += 2;
			VMDATA = @tmp;
			tmp += 2;
			VMDATA = @tmp;
			
			
			jump SNDK_LZ_JEND();
		}
		
		if( type == 1)
		{
			
			
			acc = index - pal1;
			acc = acc << 2;
			tmp = acc + opal2;
			
			VMDATA = @tmp;
			tmp += 2;
			VMDATA = @tmp;
					
			
			jump SNDK_LZ_JEND();
		}
		
		if( type == 2)
		{
			
			acc = index - pal12;
			acc = acc << 1;
			tmp = acc + opal3;
			
			VMDATA = @tmp;
			
			
		}
		
		jump SNDK_LZ_JEND();
		
		
		
		SNDK_LZ_JBEG();
		
		if( index == 0xFB)
		{
			acc = @adr ;
			
			acc &= 0xFF;
			acc += 1;
			idx = acc;
			adr += 1;
			
			buf1 = @adr;
			adr += 2;
			buf2 = @adr;
			adr += 2;
			buf3 = @adr;
			adr += 2;
			buf4 = @adr;
			adr += 2;
			
			do
			{
				VMDATA = buf1;
				VMDATA = buf2;
				VMDATA = buf3;
				VMDATA = buf4;

			}while(-- idx == 0)
			
			
			jump SNDK_LZ_JEND();
		}
		
		if( index == 0xFC)
		{
			
			VMDATA = @adr;
			adr += 2;
			
			jump SNDK_LZ_JEND();
		}
		
		if( index == 0xFD)
		{
			
			VMDATA = @adr;
			adr += 2;
			VMDATA = @adr;
			adr += 2;
			
			jump SNDK_LZ_JEND();
		}
		
		if( index == 0xFE)
		{
			
			VMDATA = @adr;
			adr += 2;
			VMDATA = @adr;
			adr += 2;
			VMDATA = @adr;
			adr += 2;
			VMDATA = @adr;
			adr += 2;
			
			jump SNDK_LZ_JEND();
		}
		
		if( index == 0xFF)
		{
			acc = @adr ;
			
			idx = acc & 0xFF;
			adr += 1;
			
			do
			{
				VMDATA = @adr;
				adr += 2;
				
			}while(-- idx == 0)
			
			
		}
		
		
		
		SNDK_LZ_JEND();
		
		
		idy -= 1;
		
		if( idy == 0)
		{
			return;
		}
	}
	while( 1 == 1);
}



void SNDK_LZ_RAM( uint16 nlabel)
{
	 uint16 opal1,opal2,opal3;
	 uint16 adr,adrh;
	
	 uint16 buf1,buf2,buf3,buf4;
	 uint16 index,pal1,pal2,pal3;
	 uint16 tmp,tmph, oadr,oadrh,i,pal12,type;
	
	
	
	nlabel = nlabel<<3;
	idx = nlabel + &SNDK_LOADR();
	
	adr  = [0x820000,idx];
	adrh = [0x820002,idx];
	tmph = adrh;
	
	oadr  = [0x820004,idx];
	oadrh = [0x820006,idx];
	
	
	
	adr += 6;
	
	
	idy = @adr;
	adr += 3;
	
	pal1 = @adr;
	adr += 1;

	pal2 = @adr;
	adr += 1;

	pal3 = @adr;
	adr += 1;
	
	pal1 &= 0xFF;
	pal2 &= 0xFF;
	pal3 &= 0xFF	;
	pal12 = 0;
	
	
	pal12 = pal1+pal2;
	
	
	
	i = 0;

	opal1 = i + adr;
	acc = pal1 << 3;
	i += acc;
	
	opal2 = i + adr;
	acc = pal2 << 2;
	i += acc;

	opal3 = i + adr;
	acc = pal3 << 1;
	i += acc;

	adr += i;
	
	index = 0;

		
	
	
	do
	{
		index = @adr;
		
		adr += 1;
		

		if( index >= 0xFB)
		{
			jump SNDK_LZR_JBEG();
		}
		
		type = 0;
		
		if( index >= pal1)
		{
			type += 1;
		}
		
		if( index >= pal12)
		{
			type += 1;
		}
		
		if( type == 0)
		{
			
			acc = index << 3;
			tmp = acc + opal1;
			
			@oadr = @tmp;
			oadr += 2;
			tmp += 2;

			@oadr = @tmp;
			oadr += 2;
			tmp += 2;
			
			@oadr = @tmp;
			oadr += 2;
			tmp += 2;
			
			@oadr = @tmp;
			oadr += 2;

			
			
			jump SNDK_LZR_JEND();
		}
		
		if( type == 1)
		{
			
			
			acc = index - pal1;
			acc = acc << 2;
			tmp = acc + opal2;
			
			@oadr = @tmp;
			oadr += 2;
			tmp += 2;
			
			@oadr = @tmp;
			oadr += 2;
					
			
			jump SNDK_LZR_JEND();
			
			
		}
		
		if( type == 2)
		{
			
			acc = index - pal12;
			acc = acc << 1;
			tmp = acc + opal3;
			
			@oadr = @tmp;
			oadr += 2;
			
			
		}
		
		jump SNDK_LZR_JEND();
		
		SNDK_LZR_JBEG();
		
		
		if( index == 0xFB)
		{
			acc = @adr ;
			
			acc &= 0xFF;
			acc += 1;
			idx = acc;
			adr += 1;
			
			buf1 = @adr;
			adr += 2;
			buf2 = @adr;
			adr += 2;
			buf3 = @adr;
			adr += 2;
			buf4 = @adr;
			adr += 2;
			
			do
			{
				@oadr = buf1;
				oadr += 2;
				@oadr = buf2;
				oadr += 2;
				@oadr = buf3;
				oadr += 2;
				@oadr = buf4;
				oadr += 2;

			}while(-- idx == 0)
			
			
			jump SNDK_LZR_JEND();
		}
		
		if( index == 0xFC)
		{
			
			@oadr = @adr;
			oadr += 2;
			adr += 2;
			
			jump SNDK_LZR_JEND();
		}
		
		if( index == 0xFD)
		{
			
			@oadr = @adr;
			oadr += 2;
			adr += 2;
			
			@oadr = @adr;
			oadr += 2;
			adr += 2;
			
			jump SNDK_LZR_JEND();
		}
		
		if( index == 0xFE)
		{
			
			@oadr = @adr;
			oadr += 2;
			adr += 2;
			
			@oadr = @adr;
			oadr += 2;
			adr += 2;
			
			@oadr = @adr;
			oadr += 2;
			adr += 2;
			
			@oadr = @adr;
			oadr += 2;
			adr += 2;
			
			jump SNDK_LZR_JEND();
		}
		
		if( index == 0xFF)
		{
			acc = @adr ;
			
			idx = acc & 0xFF;
			adr += 1;
			
			do
			{
				@oadr = @adr;
				oadr += 2;
				adr += 2;
				
			}while(-- idx == 0)
			
			
		}
		
		SNDK_LZR_JEND();
		
		
		idy -= 1;
		
		if( idy == 0)
		{
			return;
		}
	}
	while( 1 == 1);
}


void SNDK_LZ_BG()
{
	 uint16 opal1,opal2,opal3;
	 uint16 adr,adrh;
	
	 uint16 bg.w,bg.h;
	 uint16 iadr,iadrh;
	 uint16 adr2,adrh2;
	 uint16 adrc,adrhc;
	 uint16 px,py;
	
	 uint16 buf1,buf2,buf3,buf4;
	 uint16 index,pal1,pal2,pal3;
	 uint16 tmp,tmph, oadr,oadrh,i,pal12,type;
	
	
	
	tmph = adrh;
	
	oadr  = idx;
	oadrh = 0x7F;
	
	
	adr += 6;
	
	
	idy = @adr;
	adr += 3;
	
	pal1 = @adr;
	adr += 1;

	pal2 = @adr;
	adr += 1;

	pal3 = @adr;
	adr += 1;
	
	pal1 &= 0xFF;
	pal2 &= 0xFF;
	pal3 &= 0xFF	;
	pal12 = 0;
	
	
	pal12 = pal1+pal2;
	
	
	
	i = 0;

	opal1 = i + adr;
	acc = pal1 << 3;
	i += acc;
	
	opal2 = i + adr;
	acc = pal2 << 2;
	i += acc;

	opal3 = i + adr;
	acc = pal3 << 1;
	i += acc;

	adr += i;
	
	index = 0;
	
	
	
	
	
	do
	{
		index = @adr;
		
		adr += 1;
		

		if( index >= 0xFB)
		{
			jump SNDK_LZBG_JBEG();
		}
		
		type = 0;
		
		if( index >= pal1)
		{
			type += 1;
		}
		
		if( index >= pal12)
		{
			type += 1;
		}
		
		if( type == 0)
		{
			
			acc = index << 3;
			tmp = acc + opal1;
			
			@oadr = @tmp;
			oadr += 2;
			tmp += 2;

			@oadr = @tmp;
			oadr += 2;
			tmp += 2;
			
			@oadr = @tmp;
			oadr += 2;
			tmp += 2;
			
			@oadr = @tmp;
			oadr += 2;

			
			
			jump SNDK_LZBG_JEND();
		}
		
		if( type == 1)
		{
			
			
			acc = index - pal1;
			acc = acc << 2;
			tmp = acc + opal2;
			
			@oadr = @tmp;
			oadr += 2;
			tmp += 2;
			
			@oadr = @tmp;
			oadr += 2;
					
			
			jump SNDK_LZBG_JEND();
			
			
		}
		
		if( type == 2)
		{
			
			acc = index - pal12;
			acc = acc << 1;
			tmp = acc + opal3;
			
			@oadr = @tmp;
			oadr += 2;
			
			
		}
		
		jump SNDK_LZBG_JEND();
		
		SNDK_LZBG_JBEG();
		
		
		if( index == 0xFB)
		{
			acc = @adr ;
			
			acc &= 0xFF;
			acc += 1;
			idx = acc;
			adr += 1;
			
			buf1 = @adr;
			adr += 2;
			buf2 = @adr;
			adr += 2;
			buf3 = @adr;
			adr += 2;
			buf4 = @adr;
			adr += 2;
			
			do
			{
				@oadr = buf1;
				oadr += 2;
				@oadr = buf2;
				oadr += 2;
				@oadr = buf3;
				oadr += 2;
				@oadr = buf4;
				oadr += 2;

			}while(-- idx == 0)
			
			
			jump SNDK_LZBG_JEND();
		}
		
		if( index == 0xFC)
		{
			
			@oadr = @adr;
			oadr += 2;
			adr += 2;
			
			jump SNDK_LZBG_JEND();
		}
		
		if( index == 0xFD)
		{
			
			@oadr = @adr;
			oadr += 2;
			adr += 2;
			
			@oadr = @adr;
			oadr += 2;
			adr += 2;
			
			jump SNDK_LZBG_JEND();
		}
		
		if( index == 0xFE)
		{
			
			@oadr = @adr;
			oadr += 2;
			adr += 2;
			
			@oadr = @adr;
			oadr += 2;
			adr += 2;
			
			@oadr = @adr;
			oadr += 2;
			adr += 2;
			
			@oadr = @adr;
			oadr += 2;
			adr += 2;
			
			jump SNDK_LZBG_JEND();
		}
		
		if( index == 0xFF)
		{
			acc = @adr ;
			
			idx = acc & 0xFF;
			adr += 1;
			
			do
			{
				@oadr = @adr;
				oadr += 2;
				adr += 2;
				
			}while(-- idx == 0)
			
			
		}
		
		SNDK_LZBG_JEND();
		
		
		idy -= 1;
		
		if( idy == 0)
		{
			return;
		}
	}
	while( 1 == 1);
}