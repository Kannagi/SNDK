

void SNDK_ScrollMultiBG_zoneX()
{
	 uint16 bg.w,bg.h,tmp;
	
	tmp = acc;
	if( bg.w == 0x100)
	{
		acc = tmp<<1;
		return;
	}
	
	if( bg.w == 0x200)
	{
		acc = tmp<<2;
		return;
	}
	
	if( bg.w == 0x400)
	{
		acc = tmp<<3;
		return;
	}
	
	if( bg.w == 0x800)
	{
		acc = tmp<<4;
		return;
	}
	
	if( bg.w == 0x1000)
	{
		acc = tmp<<5;
		return;
	}
	
	if( bg.w == 0x2000)
	{
		acc = tmp<<6;
		return;
	}
}




void SNDK_ScrollMultiBG(uint8 flagbg)
{
	 uint16 bg.w,bg.h;
	 uint16 tmp,x2,x,py,add,vadd,zonex;
	 uint16 zonex1,zonex2;
	
	
	bg.w = SNDK_BG.w;
	bg.h = SNDK_BG.h;
	
	zonex1 = 0;
	acc = SNDK_BG2_Scroll.x&0xFF00;
	if( acc != 0)
	{
		acc += 0x100;
		acc = acc >>3;
		zonex1 = acc &0xFFC0;
	}
	
	acc = SNDK_BG2_Scroll.x&0xFE00;
	zonex2 = acc >>3	;
	
	add = SNDK_BG_Scroll.addy;
	
	
	vadd = add ;
	
	if( bg.w == 0x200)
	{
		vadd = vadd<<1;
	}
	
	if( bg.w == 0x400)
	{
		vadd = vadd<<2;
	}
	
	if( bg.w == 0x800)
	{
		vadd = vadd<<3;
	}
	
	if( bg.w == 0x1000)
	{
		vadd = vadd<<4;
	}
	
	if( bg.w == 0x2000)
	{
		vadd = vadd<<5;
	}

	
	acc = SNDK_BG2_Scroll.y&0x1F0;
	acc = acc <<1;
	acc += add;
	py = acc & 0x3E0;
	
	SNDK_VBlank.bg1.h = 0x5400+py;
	SNDK_VBlank.bg2.h = 0x5800+py;
		
	acc = SNDK_BG2_Scroll.y&0xFFF0;
	 SNDK_ScrollMultiBG_zoneX();
	x = acc;
	acc += zonex1;
	tmp = acc + vadd;
	
	SNDK_BUF_BG1.h1 = tmp + 0x4000;
	SNDK_BUF_BG2.h1 = tmp;
	
	
	
	acc = x + 0x20;
	acc = acc + zonex2;
	tmp = acc + vadd;
	
	SNDK_BUF_BG1.h2 = tmp + 0x4000;
	SNDK_BUF_BG2.h2 = tmp;
	
	
	add = SNDK_BG_Scroll.addx;
	vadd = acc << 1;
	
	acc = SNDK_BG2_Scroll.x>>4;
	acc += add;
	py = acc & 0x1F;
	
	SNDK_VBlank.bg1.v = 0x5400 + py;
	SNDK_VBlank.bg2.v = 0x5800 + py;
	
	
	if( flagbg &! 0x0A)
	{
		
		SNDK_VBlank.bg =flagbg;
		return;
		
	}
	
	 uint16 adr,adrh;
	 uint16 adr2,adrh2;
	
	zonex1 = 0;
	acc = SNDK_BG2_Scroll.y&0xFF00;
	if( acc != 0)
	{
		acc += 0x100;
		acc = acc & 0xFE00 ;
		 SNDK_ScrollMultiBG_zoneX();
		zonex1 = acc;
	}
	
	acc = SNDK_BG2_Scroll.y&0xFE00;
	 SNDK_ScrollMultiBG_zoneX();
	zonex2 = acc;
	acc = bg.w<<1;
	zonex2 += acc;

	adrh = 0x7F;
	adrh2 = 0x7F;
	
	acc = SNDK_BG2_Scroll.x>>4;
	acc = acc << 1;
	acc +=  vadd;
	tmp = acc;
	
	acc += zonex1;
	adr =  acc + &SNDK_BufferBG1;
	
	acc = tmp + zonex1;
	adr2 =  acc + &SNDK_BufferBG2;
	
	add = bg.w>>3;
	 
	idx = 0;
	idy = 0x10;
	do
	{
		SNDK_BUF_BG1.v[idx] = @adr;
		SNDK_BUF_BG2.v[idx] = @adr2;
		idx += 2;
		adr += add;
		adr2 += add;
	}
	while(-- idy == 0);
	
	acc = tmp + zonex2;
	adr =  acc + &SNDK_BufferBG1;
	
	acc = tmp + zonex2;
	adr2 =  acc + &SNDK_BufferBG2;
	
	idy = 0x10;
	do
	{
		SNDK_BUF_BG1.v[idx] = @adr;
		SNDK_BUF_BG2.v[idx] = @adr2;
		idx += 2;
		adr += add;
		adr2 += add;
	}
	while(-- idy == 0);
	
	
	
	
	SNDK_VBlank.bg =flagbg;
}
