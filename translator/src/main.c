
void main()
{
	
	TM = (SNDK_BG3);
	
	
	 SNDK_PrintLine( &STR_SELECT,0,8,25,SNDK_FONTPAL0);
	
	uint8 select,positiony;
	select = 0;
	
	uint8 fade;
	fade = 0;
	
	
	
	do
	{
		 erase_bg3();
		
		 SNDK_PrintLine( &STR_DEMO0,0,7,4,SNDK_FONTPAL0);
		 SNDK_PrintLine( &STR_DEMO1,0,7,6,SNDK_FONTPAL0);
		 SNDK_PrintLine( &STR_DEMO2,0,7,8,SNDK_FONTPAL0);
		 SNDK_PrintLine( &STR_DEMO3,0,7,10,SNDK_FONTPAL0);
		 SNDK_PrintLine( &STR_DEMO4,0,7,12,SNDK_FONTPAL0);
		 SNDK_PrintLine( &STR_DEMO5,0,7,14,SNDK_FONTPAL0);
		 SNDK_PrintLine( &STR_DEMO6,0,7,16,SNDK_FONTPAL0);
		 SNDK_PrintLine( &STR_DEMO7,0,7,18,SNDK_FONTPAL0);

		
		if( SNDK_Joypad.npad1h & SNDK_PAD_UP)
		{
			select -=1;
		}
		
		if( SNDK_Joypad.npad1h & SNDK_PAD_DOWN)
		{
			select +=1;
		}
		
		select &=7;
		
		acc = select<<1;
		positiony = acc + 4;
		 SNDK_PrintLine( &STR_SELECT2,0,4,positiony,SNDK_FONTPAL1);
		
		if( SNDK_Joypad.npad1h & SNDK_PAD_START)
		{
			fade = 1;
		}
		
		 SNDK_Fade( 6,fade);
		if( acc == 1)
		{
			if( fade == 1)
			{
				 erase_bg3();
				fade = 0;
				
				if( select == 0)
				{
					 hello();
				}
				if( select == 1)
				{
					 sprite_basic();
				}
				
				if( select == 2)
				{
					 sprite_engine();
				}
				
				if( select == 3)
				{
					 demo_bg();
				}
				
				if( select == 4)
				{
					 joypad_test();
				}
				if( select == 5)
				{
					 sound_test();
				}
				
				if( select == 6)
				{
					 music_test();
				}
				
				if( select == 7)
				{
					 hitbox_test();
				}
			}
			
		}
		
		 SNDK_WaitVBlank();
	}
	while( 1 == 1);
	
}

STR_SELECT();
const char* = "SELECT FOR QUIT";

STR_SELECT2();
const char* = "-->";

STR_DEMO0();
const char* = "TEXT";

STR_DEMO1();
const char* = "SPRITE";

STR_DEMO2();
const char* = "SPRITE ENGINE";

STR_DEMO3();
const char* = "BACKGROUND";

STR_DEMO4();
const char* = "JOYPAD";

STR_DEMO5();
const char* = "SOUND";

STR_DEMO6();
const char* = "MUSIC";

STR_DEMO7();
const char* = "HITBOX";


void erase_bg3()
{
	 SNDK_PrintLineErase( 4,4,20);
	 SNDK_PrintLineErase( 4,6,20);
	 SNDK_PrintLineErase( 4,8,26);
	 SNDK_PrintLineErase( 4,10,20);
	 SNDK_PrintLineErase( 4,12,20);
	 SNDK_PrintLineErase( 4,14,20);
	 SNDK_PrintLineErase( 4,16,20);
	 SNDK_PrintLineErase( 4,18,20);
}