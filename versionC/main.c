


int main()
{
	CSNDK_FORCED_BLANK();
	CSNDK_Init();

	CSNDK_PrintNumber8(100,2,2,0);
	while(1)
	{
		CSNDK_WaitVBlank();
	}
	return 0;
}
