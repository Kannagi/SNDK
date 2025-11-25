


int main()
{
	CSNDK_FORCED_BLANK();
	CSNDK_Init();

	uint8_t number = 0;
	uint8_t joypadA;
	uint8_t joypadB;
	
	while(1)
	{
		joypadA = CSNDK_JOYPAD1A();
		if( joypadA & 0xFF)
			number++;
		CSNDK_PrintNumber8(number,2,2,0);
		CSNDK_WaitVBlank();
	}
	return 0;
}
