
void demo_bg()
{
	
	
	
	SNDK_SendVRAM( 0x0000,MAP1_SPR,0x8000);
	
	
	SNDK_memcopy( SNDK_PALBG1,MAP1_PAL,0xE0);
	
	
	
	 SNDK_LZ_VRAM( 3);
	
	
	 SNDK_LoadBG(0,200,150);
	
	 uint8 fade;
	fade = 0;
	
	TM = (SNDK_BG1 | SNDK_BG2 | SNDK_BG3);
	
	do
	{
		if( SNDK_Joypad.pad1h & SNDK_PAD_RIGHT)
		{
			
			SNDK_BG2_Scroll.x += 1;
			SNDK_BG1_Scroll.x += 1;
			SNDK_BG_Scroll.addx = SNDK_BG_SCROLL_RIGHT;
			
		}
		
		if( SNDK_Joypad.pad1h & SNDK_PAD_LEFT)
		{
			
			SNDK_BG2_Scroll.x -= 1;
			SNDK_BG1_Scroll.x -= 1;
			SNDK_BG_Scroll.addx = SNDK_BG_SCROLL_LEFT;
			
		}
		
		
		if( SNDK_Joypad.pad1h & SNDK_PAD_UP)
		{
			
			SNDK_BG2_Scroll.y -= 1;
			SNDK_BG1_Scroll.y -= 1;
			SNDK_BG_Scroll.addy = SNDK_BG_SCROLL_UP;
			
		}
		
		if( SNDK_Joypad.pad1h & SNDK_PAD_DOWN)
		{
			
			SNDK_BG2_Scroll.y += 1;
			SNDK_BG1_Scroll.y += 1;
			SNDK_BG_Scroll.addy = SNDK_BG_SCROLL_DOWN;
			
		}
		
		
		if( SNDK_Joypad.pad1h & SNDK_PAD_SELECT)
		{
			fade = 1;
		}
		
		 SNDK_LimitBG1();
		 SNDK_LimitBG2();
		 SNDK_ScrollMultiBG( (SNDK_BG1SV | SNDK_BG1SH | SNDK_BG2SV | SNDK_BG2SH);
		
		
		( SNDK_Pause( 0xFF,0xFF);
		
		 SNDK_Fade( 6,fade);
		if( acc == 1)
		{
			if( fade == 1)
			{
				
				TM = (SNDK_BG3);
				return;
			}
		}
		 SNDK_WaitVBlank();
	}
	while( 1 == 1);
}