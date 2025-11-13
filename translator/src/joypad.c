

void joypad_test()
{
	
	
	
	uint8 key1,key2;

	uint8 fade;
	fade = 0;
	do
	{
		key1 = SNDK_Joypad.pad1h;
		key2 = SNDK_Joypad.pad1l;
		
		
		 SNDK_PrintHexa8( key1,10,8,SNDK_FONTPAL0);

		 SNDK_PrintHexa8( key2,6,8,SNDK_FONTPAL0);
		
		
		
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
		
		 SNDK_WaitVBlank();
	}
	while( 1 == 1);
}