
void PRINT_POSITION (){
	
	idx = py << 6;
	acc = px <<1;
	acc = acc & 0x1FF;
	idx += acc;
	

}

void SNDK_PrintLineFill(uint16 px,uint16 py,uint16 nc,uint16 data)
{
	PRINT_POSITION;
	
	
	idy = nc;
	do
	{		
		
		SNDK_BG3.t1[idx] = data;

		idx+=2;
		
	
	}
	while(-- idy == 0);
	
}

void SNDK_PrintLineErase(uint16 px,uint16 py,uint16 nc)
{
	PRINT_POSITION;

	idy = nc;
	do
	{		
		SNDK_BG3.t1[idx] = 0;

		idx+=2;
		
	
	}
	while(-- idy == 0);
}


void SNDK_Printchar(uint8 char,uint16 px,uint16 py,uint8 pal)
{
	PRINT_POSITION;
	SNDK_BG3.t1[idx] = char;
	SNDK_BG3.t2[idx] = pal;
}


void SNDK_Printdata(uint16 adr,uint8 ibank,uint16 px,uint16 py,uint16 nc,uint8 pal)
{
	PRINT_POSITION;

	
	idy = nc&0xFF;
	
	do
	{	
		SNDK_BG3.t1[idx] = @adr;
		SNDK_BG3.t2[idx] = pal;
		
		
		adr +=1;
		idx+=2;
		
	}
	while(-- idy == 0);
}


void SNDK_PrintLine(uint16 adr,uint8 ibank,uint16 px,uint16 py,uint8 pal)
{
	PRINT_POSITION;

	acc = @adr;
	do
	{		
		SNDK_BG3.t1[idx] = acc-32;
		SNDK_BG3.t2[idx] = pal;
		
		
		adr +=1;
		idx+=2;
		
		
		acc = @adr;
	}
	while( acc!= 0);
}

void SNDK_Print(uint16 adr,uint8 ibank,uint16 px,uint16 py,uint8 pal)
{
	 uint16 count;
	idx = 2;
	count = idx;
	
	PRINT_POSITION;
	acc = @adr;
	do
	{		
		SNDK_BG3.t1[idx] = acc-32;
		SNDK_BG3.t2[idx] = pal;
		
		
		adr +=1;
		idx+=2;
		count+=2;
		
		
		if( @adr == 0x0A)
		{
			
			idx +=0x40;
			idx  -= count;
			count = 2;
			adr +=1;
			idx+=2;
			
		}
	}
	while( @adr != 0);
}

void PRINT_HEXA (){
	acc = acc & 0xF;
	if( acc >= 0xA)
	{
		acc += 7;
	}
	acc += 0x10;
}

void PRINT_DECIMAL100 (){
	if( tnumber >= 100)
	{
		tnumber -= 100;
		.arg1 += 1;
	}
	
	if( tnumber >= 100)
	{
		tnumber -= 100;
		.arg1 += 1;
	}

}

void PRINT_DECIMAL (){
	
	if( tnumber >= .arg1)
	{
		tnumber -= .arg1;
		.arg4 += 5;
	}
	
	
	if( tnumber >= .arg2)
	{
		tnumber -= .arg2;
		.arg4 += 2;
	}
	
	
	if( tnumber >= .arg2)
	{
		tnumber -= .arg2;
		.arg4 += 2;
	}
	
	
	if( tnumber >= .arg3)
	{
		tnumber -= .arg3;
		.arg4 += 1;
	}

}

void SNDK_PrintNumber8(uint8 number,uint16 px,uint16 py,uint8 pal)
{
	PRINT_POSITION;
	
	 uint8 tnumber1,tnumber2,tnumber;
	tnumber = number;
	tnumber1 = 0x10;
	tnumber2 = acc;
	
	PRINT_DECIMAL100 tnumber1;
	SNDK_BG3.t1[idx] = tnumber1;
	SNDK_BG3.t2[idx] = pal;
	idx+=2;
	
	PRINT_DECIMAL 50,20,10,tnumber2;
	SNDK_BG3.t1[idx] = tnumber2;
	SNDK_BG3.t2[idx] = pal;
	idx+=2;
	
	SNDK_BG3.t1[idx] = tnumber + 0x10;
	SNDK_BG3.t2[idx] = pal;
}

void SNDK_PrintNumber8M(uint8 number,uint16 px,uint16 py,uint8 pal)
{
	PRINT_POSITION;
	
	 uint8 tnumber2,tnumber;
	tnumber = number;
	tnumber2 = 0x10;
	
	PRINT_DECIMAL 50,20,10,tnumber2;
	SNDK_BG3.t1[idx] = tnumber2;
	SNDK_BG3.t2[idx] = pal;
	idx+=2;
	
	SNDK_BG3.t1[idx] = tnumber + 0x10;
	SNDK_BG3.t2[idx] = pal;
}

void SNDK_PrintNumber16(uint16 number,uint16 px,uint16 py,uint8 pal)
{
	PRINT_POSITION;
	
	
	
	 uint16 tnumber1,tnumber2,tnumber3,tnumber4,tnumber;
	tnumber = number;
	tnumber1 = 0x10;
	tnumber2 = acc;
	tnumber3 = acc;
	tnumber4 = acc;
	
	PRINT_DECIMAL 50000,20000,10000,tnumber1;
	PRINT_DECIMAL 5000,2000,1000,tnumber2;
	PRINT_DECIMAL 500,200,100,tnumber3;
	PRINT_DECIMAL 50,20,10,tnumber4;
	
	
	SNDK_BG3.t1[idx] = tnumber1;
	SNDK_BG3.t2[idx] = pal;
	idx+=2;
	
	
	SNDK_BG3.t1[idx] = tnumber2;
	SNDK_BG3.t2[idx] = pal;
	idx+=2;
	
	SNDK_BG3.t1[idx] = tnumber3;
	SNDK_BG3.t2[idx] = pal;
	idx+=2;
	
	SNDK_BG3.t1[idx] = tnumber4;
	SNDK_BG3.t2[idx] = pal;
	idx+=2;
	
	SNDK_BG3.t1[idx] = tnumber + 0x10;
	SNDK_BG3.t2[idx] = pal;
}



void SNDK_PrintHexa8(uint8 number,uint16 px,uint16 py,uint8 pal)
{
	PRINT_POSITION;
	
	acc = number>>4;
	PRINT_HEXA;
	SNDK_BG3.t1[idx] = acc;
	SNDK_BG3.t2[idx] = pal;
	idx+=2;
	
	acc = number;
	PRINT_HEXA;
	SNDK_BG3.t1[idx] = acc;
	SNDK_BG3.t2[idx] = pal;
}

void SNDK_PrintHexa16(uint16 number,uint16 px,uint16 py,uint8 pal)
{
	 uint16 tnumber2,tnumber3;
	
	PRINT_POSITION;
	
	acc = number;
	tnumber3 = acc>>4;
	tnumber2 = acc>>4;
	acc = acc>>4;
	
	
	
	PRINT_HEXA;
	SNDK_BG3.t1[idx] = acc;
	SNDK_BG3.t2[idx] = pal;
	idx+=2;
	
	acc = tnumber2;
	PRINT_HEXA;
	SNDK_BG3.t1[idx] = acc;
	SNDK_BG3.t2[idx] = pal;
	idx+=2;
	
	acc = tnumber3;
	PRINT_HEXA;
	SNDK_BG3.t1[idx] = acc;
	SNDK_BG3.t2[idx] = pal;
	idx+=2;
	
	acc = number;
	PRINT_HEXA;
	SNDK_BG3.t1[idx] = acc;
	SNDK_BG3.t2[idx] = pal;
}



void SNDK_PrintDec2(uint8 number,uint16 px,uint16 py,uint8 pal)
{
	PRINT_POSITION;
	
	acc = number>>4;
	acc += 0x10;
	SNDK_BG3.t1[idx] = acc;
	SNDK_BG3.t2[idx] = pal;
	idx+=2;
	
	acc = number &0x0F;
	acc += 0x10;
	SNDK_BG3.t1[idx] = acc;
	SNDK_BG3.t2[idx] = pal;
}

void SNDK_PrintDec4(uint16 number,uint16 px,uint16 py,uint8 pal)
{
	PRINT_POSITION;
	
	 uint8 tnumber,tnumber2;
	
	tnumber = number;
	
	
	acc = tnumber2>>4;
	acc += 0x10;
	SNDK_BG3.t1[idx] = acc;
	SNDK_BG3.t2[idx] = pal;
	idx+=2;
	
	acc = tnumber2 &0x0F;
	acc += 0x10;
	SNDK_BG3.t1[idx] = acc;
	SNDK_BG3.t2[idx] = pal;
	idx +=2;
	
	acc = number>>4;
	acc += 0x10;
	SNDK_BG3.t1[idx] = acc;
	SNDK_BG3.t2[idx] = pal;
	idx+=2;
	
	acc = number &0x0F;
	acc += 0x10;
	SNDK_BG3.t1[idx] = acc;
	SNDK_BG3.t2[idx] = pal;
}

void SNDK_PrintDec8(uint16 number,uint16 number2,uint16 px,uint16 py,uint8 pal)
{
	PRINT_POSITION;
	
	 uint8 tnumber,tnumber2;
	
	tnumber = number;
	
	
	acc = tnumber2>>4;
	acc += 0x10;
	SNDK_BG3.t1[idx] = acc;
	SNDK_BG3.t2[idx] = pal;
	idx+=2;
	
	acc = tnumber2 &0x0F;
	acc += 0x10;
	SNDK_BG3.t1[idx] = acc;
	SNDK_BG3.t2[idx] = pal;
	idx +=2;
	
	acc = number>>4;
	acc += 0x10;
	SNDK_BG3.t1[idx] = acc;
	SNDK_BG3.t2[idx] = pal;
	idx+=2;
	
	acc = number &0x0F;
	acc += 0x10;
	SNDK_BG3.t1[idx] = acc;
	SNDK_BG3.t2[idx] = pal;
	idx+=2;
	
	
	
	tnumber = number2;
	
	
	acc = tnumber2>>4;
	acc += 0x10;
	SNDK_BG3.t1[idx] = acc;
	SNDK_BG3.t2[idx] = pal;
	idx+=2;
	
	acc = tnumber2 &0x0F;
	acc += 0x10;
	SNDK_BG3.t1[idx] = acc;
	SNDK_BG3.t2[idx] = pal;
	idx +=2;
	
	acc = number2>>4;
	acc += 0x10;
	SNDK_BG3.t1[idx] = acc;
	SNDK_BG3.t2[idx] = pal;
	idx+=2;
	
	acc = number2 &0x0F;
	acc += 0x10;
	SNDK_BG3.t1[idx] = acc;
	SNDK_BG3.t2[idx] = pal;
}