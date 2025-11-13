



void SNDK_zorder(uint8 count)
{
	if( count == 0)
	{
		return;
	}
	
	if( count >= 16)
	{
		return;
	}
	
	 uint8 order,ay,ax,tmp,value;
	 uint16 tarray 0x10;
	
	
	acc = count&0x1F;
	idx = acc << 1;
	
	
	tarray = 0;
	acc = 0;
	do
	{
		tarray[idx] = acc;
		
	}
	while(-- idx == 0);

	
	
	idy = count&0x1F;
	
	
	do
	{
		idx = idy;
		ay = SNDK_ZBUFFER[idx];
		order = 0;
		
		
		idx = count&0x1F;
		

		do
		{
			ax = SNDK_ZBUFFER[idx];
			if( ax < ay)
			{
				order += 1;
			}
			
		}
		while(-- idx == 0);
		
		
		idx = order&0x1F;
		
		
		value = 0;
		tmp = tarray[idx];
		if( acc != 0)
		{
			value = tmp;
		}
		
		tarray[idx] = tmp + 1;
		
		idx = idy;
		SNDK_ZBUFFER_OUT[idx] = order + value;
		
		
	}
	while(-- idy == 0);
	
	return ;

}