
STR_SOUND();
const char* = "PRESS A OR B";


void sound_test()
{
	
	
	
	 SNDK_SPC_Set2( SNDK_SPC_ADDR,0x700);
	 SNDK_SPC_SetData( &SFX_DIR,0,0x100);
	
	
	 SNDK_SPC_Set2( SNDK_SPC_ADDR,0x8000);
	 SNDK_SPC_SetData( &SFX_BRR,0,0x5000);
	
	
	 SNDK_SPC_Set( SNDK_SPC_VOLUME,0x7F,0x7F);
	 SNDK_SPC_Set( SNDK_SPC_BRR_VOLUME,0x7F,0x7F);
	
	
	 SNDK_PrintLine( &STR_SOUND,0,8,4,SNDK_FONTPAL0);
	
	uint8 key1,key2;

	uint8 fade;
	fade = 0;
	do
	{
		if( SNDK_Joypad.npad1l & SNDK_PAD_A)
		{
			SNDK_SFX1 = 0 ;
		}
		
		if( SNDK_Joypad.npad1h & SNDK_PAD_B)
		{
			SNDK_SFX2 = 1 ;
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
				return;
			}
		}
		
		
		 SNDK_SFX_Engine( 12);
		
		 SNDK_WaitVBlank();
	}
	while( 1 == 1);
}