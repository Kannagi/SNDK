
STR_CPU();
const char* = "CPU";

STR_HELLO();
const char* = "HELLO WORLD";

void hello()
{
	
	
	 uint8 var1,var2,var3;
	
	 SNDK_PrintLine( &STR_HELLO,0,10,4,SNDK_FONTPAL0);
	
	
	
	

	
	 uint8 fade;
	fade = 0;
	
	var1 = 0x10;
	
	var2 = 33;
	
	var3 = 0xAB;
	
	
	 uint16 var4,var5,var6,bvar1,bvar2;
	
	
	
	var4 = 0x1023;
	
	var5 = 1033;
	
	var6 = 0x1FAB;
	
	
	bvar1 = 0x1000;
	bvar2 = 0x2000;
	
	
		
	do
	{
		 SNDK_PrintLine( &STR_CPU,0,4,6,SNDK_FONTPAL0);
		
		 SNDK_PrintNumber8( SNDK.pcpu,8,6,SNDK_FONTPAL0);
		
		
		
		 SNDK_PrintDec2( var1,4,8,SNDK_FONTPAL0);
		
		 SNDK_PrintNumber8( var2,10,8,SNDK_FONTPAL0);
		
		 SNDK_PrintHexa8( var3,16,8,SNDK_FONTPAL0);
		
		
		 SNDK_PrintDec4( var4,4,10,SNDK_FONTPAL0);
		
		 SNDK_PrintNumber16( var5,10,10,SNDK_FONTPAL0);
		
		 SNDK_PrintHexa16( var6,16,10,SNDK_FONTPAL0);
		
		
		 SNDK_PrintDec8( bvar1,bvar2,6,12,SNDK_FONTPAL0);
		
		
		SNDK_AddDec var1,1 ;
		var1 = acc;
		var2 +=1;
		var3 +=1;
		
		if( SNDK_Joypad.pad1h & SNDK_PAD_SELECT)
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