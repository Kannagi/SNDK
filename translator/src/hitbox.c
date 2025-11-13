
STR_HITBOX1();
const char* = "HITBOX:OK";

STR_HITBOX2();
const char* = "HITBOX:NO";



void hitbox_test()
{
	
	
	
	SNDK_SendVRAM( 0x6000,SPRITE1_SPR,0x1000);
	
	
	SNDK_memcopy( SNDK_PALSPR0,SPRITE1_PAL,0x40);
	
	SNDK_SendCGRAM 0x00,SNDK_PALBG0,0x200;
	
	 uint8 fade;
	fade = 0;
	
	TM = (SNDK_OBJ | SNDK_BG3);
	
	 uint16 px,py,hit;
	
	
	px = 100;
	py = 100;
	
	
	do
	{

		 SNDK_Sprite();
		
		
		 SNDK_SpriteDraw( px,py,0x00,0x00,0x03);
		
		
		 SNDK_SpriteDrawMeta2x2( 100,140,0x04,0x00,0x00);
		
		
		 SNDK_SpriteDrawMeta2x2( 160,40,0x04,0x00,0x00);
		
		
		if( SNDK_Joypad.pad1h & SNDK_PAD_RIGHT)
		{
			px += 2;
		}
		
		if( SNDK_Joypad.pad1h & SNDK_PAD_LEFT)
		{
			px -= 2;
		}
		
		if( SNDK_Joypad.pad1h & SNDK_PAD_UP)
		{
			py -= 2;
		}
		
		if( SNDK_Joypad.pad1h & SNDK_PAD_DOWN)
		{
			py += 2;
		}
		
		
		
		hit = 0;
		
		 SNDK_HitboxSet( px,py,32,32);
		
		 SNDK_HitboxAABB( 100,140,32,32);
		hit += acc;
		
		 SNDK_HitboxAABB( 160,40,32,32);
		hit += acc;
		
		
		if( px & 0xFF00)
		{
			hit = 0;
		}
		
		
		
		if( hit == 0)
		{
			 SNDK_PrintLine( &STR_HITBOX2,0,10,4,SNDK_FONTPAL0);
		}
		else
		{
			 SNDK_PrintLine( &STR_HITBOX1,0,10,4,SNDK_FONTPAL0);
		}
		
		
		if( SNDK_Joypad.pad1h & SNDK_PAD_SELECT)
		{
			fade = 1;
		}
		
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