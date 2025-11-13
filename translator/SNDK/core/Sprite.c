
void SNDK_Sprite_SetOAM( uint16 oam)
{
	
	SNDK_Sprite.oam = oam<<2;
	
}



void SNDK_SpriteEngine(uint16 oam,uint16 n,uint8 ndma)
{

	 uint16 posx,posy;
	 uint8 tile,attribute,draw,draw2;
	 uint16 posxh,indexh;
	 uint16 fptr,oldx;
		
	
	if( n >= 16)
	{
		n = 16;
	}
	
	if( n == 0)
	{
		return;
	}
	
	 SNDK_SpriteEngineDMA( oam,n,ndma);
	

	
	
	idy = n;
	idx = 0;
	SNDK_Sprite.oam = oam<<2;
	
	do
	{			
		SNDK_SPRITE.x[idx]  +=  SNDK_SPRITE.vx[idx];
		posx = acc>>2;
		posx += SNDK_SPRITE.offsetx[idx];
		
		SNDK_SPRITE.y[idx]  +=  SNDK_SPRITE.vy[idx];
		posy = acc>>2;
		posy += SNDK_SPRITE.offsety[idx];
		
		tile = SNDK_SPRITE.t[idx] ;
		
		fptr = SNDK_SPRITE.mode[idx];
		
		oldx = idx;
		 fptr;
		
		
		idx+= 0x20;
	}
	while(-- idy == 0);

	
	
}

void SNDK_SpriteEngineDMA(uint16 oam,uint16 n,uint8 ndma)
{
	 uint16 posx,posy;
	 uint8 tile,attribute,draw,draw2;
	 uint16 posxh,indexh;
	 uint16 fptr,oldx;
	
	uint16 dma_count;
	
	
	 uint16 list,add,ianim,lista,bank;
	 uint8 nanim,index;
	
	
	
	idx = dma_count << 5;
	oldx = idx;
	
	index = SNDK_SPRITE.index[idx];
	ianim = SNDK_SPRITE.ianim[idx];
	SNDK_SPRITE.ianim[idx] = ianim + 2;
	list = SNDK_SPRITE.list[idx];
	lista = [0x820004,list] + index;
	nanim = [0x820000,lista];
	idx = lista + ianim;
	add = [0x820002,idx] & 0xFFF0;
	bank = [0x820002,idx] & 0xF;
	
	idx = list;
	SNDK_VBlank.dma_spr1.addr = [0x820000,idx] + add;
	SNDK_VBlank.dma_spr1.size = [0x82000A,idx];
	SNDK_VBlank.dma_spr1.add = [0x82000C,idx];
	SNDK_VBlank.dma_spr1.vmaddr = [0x820008,idx];
	
	
	if( ndma == 0)
	{
		return;
	}
	
	SNDK_VBlank.dma_spr1.bank = [0x820002,idx] + bank;
	SNDK_VBlank.dma_spr1.channel = [0x82000E,idx];
	
	
	SNDK_SPRITE.eanim[oldx] = 0;
	if( ianim == nanim)
	{
		SNDK_SPRITE.ianim[oldx] = 0;
		SNDK_SPRITE.eanim[oldx] = 1;
	}
	
	SNDK_SPRITE.bank[oldx] = bank;
	
	SNDK_SPRITE.add[oldx] = add;
	
	
	oldx += 0x20;
	idx = oldx;
		
	acc = ndma&3;
	if( acc == 2)
	{
		index = SNDK_SPRITE.index[idx];
		ianim = SNDK_SPRITE.ianim[idx];
		SNDK_SPRITE.ianim[idx] = ianim + 2;
		list = SNDK_SPRITE.list[idx];
		lista = [0x820004,list] + index;
		nanim = [0x820000,lista];
		idx = lista + ianim;
		add = [0x820002,idx] & 0xFFF0;
		bank = [0x820002,idx] & 0xF;
		
		idx = list;
		SNDK_VBlank.dma_spr2.addr = [0x820000,idx] + add;
		SNDK_VBlank.dma_spr2.size = [0x82000A,idx];
		SNDK_VBlank.dma_spr2.add = [0x82000C,idx];
		SNDK_VBlank.dma_spr2.vmaddr = [0x820008,idx];
	}
	
	

	if( ndma == 2)
	{
		SNDK_VBlank.dma_spr2.bank = [0x820002,idx] + bank;
		SNDK_VBlank.dma_spr2.channel = [0x82000E,idx];
		
		SNDK_SPRITE.eanim[oldx] = 0;
		if( ianim == nanim)
		{
			SNDK_SPRITE.ianim[oldx] = 0;
			SNDK_SPRITE.eanim[oldx] = 1;
		}
		
		SNDK_SPRITE.bank[oldx] = bank;
		
		SNDK_SPRITE.add[oldx] = add;
		
	}
	
	
	
	
	dma_count +=ndma;
	if( dma_count >= n)
	{
		dma_count = 0;
	}
}




void SNDK_Init_SpriteList(uint16 sindex, uint16 nlist,uint8 tile,uint8 attrib,uint16 pfunc)
{
	
	idx = sindex;
	
	nlist = nlist<<4;
	
	SNDK_SPRITE.list[idx] = &SNDK_LIST( + nlist);
	SNDK_SPRITE.mode[idx] = pfunc;
	
	acc = 0;
	SNDK_SPRITE.index[idx] = acc;
	SNDK_SPRITE.x[idx] = acc;
	SNDK_SPRITE.y[idx] = acc;
	SNDK_SPRITE.add[idx] = acc;
	SNDK_SPRITE.ianim[idx] = acc;
	SNDK_SPRITE.visible[idx] = acc;
	
	
	SNDK_SPRITE.oam[idx] = acc;
	SNDK_SPRITE.flag[idx] = acc;
	SNDK_SPRITE.eanim[idx] = acc;
	SNDK_SPRITE.draw[idx] = acc;
	
	SNDK_SPRITE.t[idx] = tile;
	SNDK_SPRITE.a[idx] = attrib;
}