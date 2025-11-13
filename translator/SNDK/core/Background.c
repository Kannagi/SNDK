
void SNDK_UnpackBG()
{
	 uint16 data,rle,data2;
	 uint16 adr,adrh;
	
	
	idy = @adr;
	adr +=2;
	do
	{
		acc = @adr		;
		adr += 2;
		if( acc &1)
		{
			data = acc&0xFFFE;
			rle = @adr;
			adr += 1;
			idy -=1;
			
			asm "phy";

			idy = rle&0x3F;
			idy +=1;
			
			if( rle & 0x80)
			{
				data2 = data + 2;
				idy -=1;
				do
				{
					[0x7F0000,idx] = data;
					idx += 2;
					[0x7F0000,idx] = data2;
					idx += 2;
				}
				while(-- idy == 0);
				
			}else
			{
				if( rle & 0x40)
				{
					acc = data;
					do
					{
						[0x7F0000,idx] = acc;
						idx += 2;
						acc += 2;
					}
					while(-- idy == 0);
					
				}else
				{
					
					acc = data;
					do
					{
						[0x7F0000,idx] = acc;
						idx += 2;
					}
					while(-- idy == 0);
					
				}
			}
			asm "ply";
		}else
		{
			[0x7F0000,idx] = acc;
			idx += 2;
		}	
		
		idy -=1	;
		
	}
	while(-- idy == 0);
}

void SNDK_UnpackBGC()
{
	 uint16 data,rle,data2;
	 uint16 adr,adrh,tmp;
	
	
	idy = @adr;
	adr +=2;
	rle = 0;
	
	do
	{
		acc = @adr;
		tmp = acc;
		
		adr += 1;
		

		if( tmp & 0x80)
		{
			data = acc&0x7F;
			rle = @adr;
			
			adr += 1;
			
			idy -= 1;
			
			asm "phy";
			idy = rle;
			idy += 1;
			
			
			acc = data;
			do
			{
				[0x7F0000,idx] = acc;
				idx += 1;
				
			}
			while(-- idy == 0);
			
					
			asm "ply";
		}else
		{
			[0x7F0000,idx] = acc;
			idx += 1;
			
		}	
			
		
	}
	while(-- idy == 0);
	
	
}



void SNDK_LoadBG(uint16 ilist,uint16 ipx,uint16 ipy)
{
	 uint16 data,rle,data2;
	 uint16 iadr,iadrh;
	 uint16 bg.w,bg.h;
	 uint16 adr,adrh;
	 uint16 adr2,adrh2;
	 uint16 adrc,adrhc;
	 uint16 px,py;
	 uint16 pos,add;
	
	
	idx = ilist <<4;
	
	adr = [SNDK_MAPLIST,idx];
	idx +=2;
	
	adrh = [SNDK_MAPLIST,idx];
	idx +=2;
	
	adr2 = [SNDK_MAPLIST,idx];
	idx +=2;
	
	adrh2 = [SNDK_MAPLIST,idx];
	idx +=2;
	
	adrc = [SNDK_MAPLIST,idx];
	idx +=2;
	
	adrhc = [SNDK_MAPLIST,idx];
	idx +=2;
	
	SNDK_BG.w = [SNDK_MAPLIST,idx];
	idx += 2;
	SNDK_BG.h = [SNDK_MAPLIST,idx];
	
	px = ipx&0xFEFF;
	py = ipy&0xFEFF;
	
	if( ipx & 0x100)
	{
		px |= 0xFF;
	}
	
	if( ipy & 0x100)
	{
		py |= 0xFF;
	}
	
	SNDK_BG1_Scroll.x = px;
	SNDK_BG2_Scroll.x = px;
	
	SNDK_BG1_Scroll.y = py;
	SNDK_BG2_Scroll.y = py;
	
	
	
	
	
	
	idx = &SNDK_BufferBG2;
	iadr = adr;
	iadrh = adrh;
	if( adrh != 0)
	{
		 SNDK_LZ_BG();
		
		
	}
	
	idx = &SNDK_BufferBG1;
	iadr = adr2;
	iadrh = adrh2;
	
	if( adrh2 != 0)
	{
		 SNDK_LZ_BG();
		
		
	}
	
	idx = &SNDK_BufferBGC;
	iadr = adrc;
	iadrh = adrhc;
	
	
	if( adrhc != 0)
	{
		 SNDK_UnpackBGC();
	}
	
	
	
	bg.w = SNDK_BG.w>>3;
	
	
	py = py &0xFE00;
	py = py<<1;
	
	if( SNDK_BG.w == 0x200)
	{
		py = py<<1;
	}
	
	if( SNDK_BG.w == 0x400)
	{
		py = py<<2;
	}
	
	if( SNDK_BG.w == 0x800)
	{
		py = py<<3;
	}
	
	if( SNDK_BG.w == 0x1000)
	{
		py = py<<4;
	}
	
	if( SNDK_BG.w == 0x2000)
	{
		py = py<<5;
	}
	
	
	acc = px &0xFE00;
	px = acc>>3;
	
	pos = px + py;
	
	VMADD = 0x5400;
	
	if( adrh2 != 0)
	{
		idy = 0x20;
		add = &SNDK_BufferBG1 + pos;
		do
		{
			DMA_ADD_0 = add;
			DMA_SIZE_0 = 0x40;
			
			
			DMA_BANK_0 = 0x7F;
			MDMAEN = 0x01;
			

			add += bg.w;
		}
		while(-- idy == 0);
		
	}
	

	if( adrh == 0)
	{
		
		return;
		
	}
	
	
	VMADD = 0x5800;
	idy = 0x20;
	add = &SNDK_BufferBG2 + pos;
	do
	{
		DMA_ADD_0 = add;
		DMA_SIZE_0 = 0x40;
		
		
		DMA_BANK_0 = 0x7F;
		MDMAEN = 0x01;
		

		add += bg.w;
	}
	while(-- idy == 0);
	
	
	
	return;

	
}

void SNDK_LimitBG1()
{
	 uint16 tmp;
	
	if( SNDK_BG1_Scroll.x &0xC000)
	{
		SNDK_BG1_Scroll.x = 0;
	}
	
	if( SNDK_BG1_Scroll.y &0xC000)
	{
		SNDK_BG1_Scroll.y = 0;
	}
	
	
	tmp = SNDK_BG1_Scroll.x +256;
	if( tmp >= 1024)
	{
		SNDK_BG1_Scroll.x = SNDK_BG.w-256;
	}
	
	tmp = SNDK_BG1_Scroll.y +225;
	if( tmp >= 1024)
	{
		SNDK_BG1_Scroll.y = SNDK_BG.h-225;
	}
	
	
}

void SNDK_LimitBG2()
{
	 uint16 tmp;
	
	if( SNDK_BG2_Scroll.x &0xC000)
	{
		SNDK_BG2_Scroll.x = 0;
	}
	
	if( SNDK_BG2_Scroll.y &0xC000)
	{
		SNDK_BG2_Scroll.y = 0;
	}
	
	
	tmp = SNDK_BG2_Scroll.x +256;
	if( tmp >= SNDK_BG.w)
	{
		SNDK_BG2_Scroll.x = SNDK_BG.w-256;
	}
	
	tmp = SNDK_BG2_Scroll.y +225;
	if( tmp >= SNDK_BG.h)
	{
		SNDK_BG2_Scroll.y = SNDK_BG.h-225;
	}
	
	
}