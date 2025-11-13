
STR_MUSIC();
const char* = "PRESS A REPLAY";


STR_MUSIC2();
const char* = "PRESS B STOP";

void music_test()
{
	
	
	
	 SNDK_SPC_Set2( SNDK_SPC_ADDR,0x800);
	 SNDK_SPC_SetData( &MUSIC_TRACK1,0,0x2000);
	
	
	 SNDK_SPC_Set2( SNDK_SPC_ADDR,0x4000);
	 SNDK_SPC_SetData( &MUSIC_BRR,0,0x8000);
	
	
	
	
	
	 SNDK_SPC_Set( SNDK_SPC_VOLUME,0x0F,0x0F);
	 SNDK_SPC_Set( SNDK_SPC_BRR_VOLUME,0x7F,0x7F);
	
	 SNDK_SPC_Set2(  SNDK_SPC_PLAY,SNDK_SPC_ON);
	
	
	 SNDK_PrintLine( &STR_MUSIC,0,8,4,SNDK_FONTPAL0);
	
	 SNDK_PrintLine( &STR_MUSIC2,0,8,6,SNDK_FONTPAL0);
	
	uint8 key1,key2;

	uint8 fade;
	fade = 0;
	do
	{
		if( SNDK_Joypad.npad1l & SNDK_PAD_A)
		{
			 SNDK_SPC_Set2(  SNDK_SPC_PLAY,SNDK_SPC_REPLAY);
		}
		
		if( SNDK_Joypad.npad1h & SNDK_PAD_B)
		{
			 SNDK_SPC_Set2(  SNDK_SPC_PLAY,SNDK_SPC_STOP);
		}
		
		
		
		if( SNDK_Joypad.npad1h & SNDK_PAD_SELECT)
		{
			fade = 1;
		}
		
		 SNDK_Fade( 6,fade);
		if( acc == 1)
		{
			if( fade == 1)
			{
				 SNDK_SPC_Set2(  SNDK_SPC_PLAY,SNDK_SPC_STOP);
				return;
			}
		}
		
		
		 SNDK_SFX_Engine( 12);
		
		 SNDK_WaitVBlank();
	}
	while( 1 == 1);
}