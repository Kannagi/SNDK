
void SNDK_wramcopy( uint16 dstl, uint8 dstb, uint16 srcl, uint8 srcb, uint16 size)
{
	
	WMADD = dstl;
	DMA_ADD_6 = srcl;
	DMA_SIZE_6 = size;
	
	
	WMADDH = dstb;
	DMA_BANK_6 = srcb;
	
	MDMAEN = 0x40;
}


SNDK_str_pause();
const char* = "PAUSE";

void SNDK_Pause(uint8 sfx1,uint8 sfx2)
{
	if( SNDK_Joypad.npad1h & SNDK_PAD_START)
	{

		SNDK_Joypad.npad1h = 0;
		SNDK_SFX1 = sfx1;
	}else
	{
		if( SNDK_Joypad.npad2h & SNDK_PAD_START)
		{

			SNDK_Joypad.npad2h = 0;
			SNDK_SFX1 = sfx1;
		}else
		{
			return;
		}
	}
	
	 SNDK_PrintLine( &SNDK_str_pause,0,14,13,SNDK_FONTPAL0);
	do
	{
		
		if( SNDK_Joypad.npad1h & SNDK_PAD_START)
		{
			SNDK_SFX1 = sfx2;
			 SNDK_PrintLineErase( 14,13,5);
			return;
		}
		
		if( SNDK_Joypad.npad2h & SNDK_PAD_START)
		{
			SNDK_SFX1 = sfx2;
			 SNDK_PrintLineErase( 13,13,5);
			return;
		}
		
		 SNDK_SFX_Engine( 3);
		 SNDK_WaitVBlank();
	}
	while( 1);

}

void SNDK_Fade( uint8 ncount , uint8 dirf)
{
	uint8 count;
	
	if( dirf == 0xFF)
	{
		return 2;
	}
	
	if( dirf != 0)
	{
		
		if( SNDK_Light == 0)
		{
			return 1;
		}
	}else
	{
		
		if( SNDK_Light == 0xF)
		{
			return 1;
		}
	}
	
	count += 1;
	
	if( count == ncount)
	{
		if( dirf == 0)
		{
			SNDK_Light += 1;
		}else
		{
			SNDK_Light -= 1;
		}
		
		count = 0;
	}
	
	return 0;
}

void rand()
{
	
	acc = SNDK_vrand;
	
	acc = acc << 5;
	acc ^= acc;
	
	acc = acc >> 6;
	acc ^= acc;
	
	acc = acc << 2;
	acc ^= acc;
	
	SNDK_vrand = acc;
	

	
}
	