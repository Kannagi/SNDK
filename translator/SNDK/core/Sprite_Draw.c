

void SNDK_SpriteDraw(uint16 position.x,uint8 position.y,uint8 tile,uint8 attribute,uint8 flag)
{
	idx = SNDK_Sprite.oam;
	
	SNDK_OAM0.x[idx] = position.x;
	SNDK_OAM0.y[idx] = position.y;
	SNDK_OAM0.t[idx] = tile;
	SNDK_OAM0.a[idx] = attribute;
	
	 uint16 indexh;
	
	
	SNDK_Sprite.oam = idx + 4;
	indexh = acc>>4;
	
	if( position.x &! 0xFF00)
	{
		flag = flag&0xAA;
	}
	
	
	SNDK_OAMH[indexh] |= flag ;
}

void SNDK_SpriteDrawClip(uint16 position.x,uint16 position.y,uint8 tile,uint8 attribute,uint8 flag)
{
	
	
	if( position.x & 0xFF00)
	{
		acc = position.x + 32;
		if( acc & 0xFF00)
		{
			SNDK_Sprite.oam += 4;
			
			return;
			
		}
	}
	
	
	if( position.y & 0xFF00)
	{
		acc = position.y + 32;
		if( acc & 0xFF00)
		{
			SNDK_Sprite.oam += 4;
			
			return;
			
		}
	}else
	{
		acc = position.y &0xE0;
		if( acc == 0xE0)
		{
			SNDK_Sprite.oam += 4;
			
			return;
		}
	}
	
	
	
	
	
	
	idx = SNDK_Sprite.oam;
	
	SNDK_OAM0.x[idx] = position.x;
	SNDK_OAM0.y[idx] = position.y;
	SNDK_OAM0.t[idx] = tile;
	SNDK_OAM0.a[idx] = attribute;
	
	 uint16 indexh;
	
	
	SNDK_Sprite.oam = idx + 4;
	indexh = acc>>4;
	
	if( position.x &! 0xFF00)
	{
		flag = flag&0xAA;
	}
	
	
	SNDK_OAMH[indexh] |= flag ;
}

void SNDK_SpriteDrawMeta2x2Clip(uint16 position.x,uint16 position.y,uint8 tile,uint8 attribute,uint8 flag)
{
	
	
	if( position.x & 0xFF00)
	{
		acc = position.x + 64;
		if( acc & 0xFF00)
		{
			SNDK_Sprite.oam += 16;
			
			return;
			
		}
	}
	
	
	if( position.y & 0xFF00)
	{
		acc = position.y + 32;
		if( acc & 0xFF00)
		{
			SNDK_Sprite.oam += 16;
			
			return;
			
		}
	}else
	{
		acc = position.y &0xE0;
		if( acc == 0xE0)
		{
			SNDK_Sprite.oam += 16;
			
			return;
		}
	}
	
	
	
	
	
	idx = SNDK_Sprite.oam;
	
	SNDK_OAM0.x[idx] = position.x;
	SNDK_OAM2.x[idx] = acc;
	SNDK_OAM1.x[idx] = acc+SNDK_SPR_SIZE;
	SNDK_OAM3.x[idx] = acc;
	
	SNDK_OAM0.y[idx] = position.y;
	SNDK_OAM1.y[idx] = acc;
	SNDK_OAM2.y[idx] = acc+SNDK_SPR_SIZE;
	SNDK_OAM3.y[idx] = acc;
	
	SNDK_OAM0.t[idx] = tile;
	SNDK_OAM1.t[idx] = acc+SNDK_SPR_SIZET;
	SNDK_OAM2.t[idx] = tile+SNDK_SPR_DEC;
	SNDK_OAM3.t[idx] = acc+SNDK_SPR_SIZET;
	
	if( attribute & OAM_YFLIP)
	{
		if( attribute & OAM_XFLIP)
		{
			SNDK_OAM3.t[idx] = tile;
			SNDK_OAM2.t[idx] = acc+SNDK_SPR_SIZET;
			SNDK_OAM1.t[idx] = tile+SNDK_SPR_DEC;
			SNDK_OAM0.t[idx] = acc+SNDK_SPR_SIZET;
		}else
		{
			SNDK_OAM2.t[idx] = tile;
			SNDK_OAM3.t[idx] = acc+SNDK_SPR_SIZET;
			SNDK_OAM0.t[idx] = tile+SNDK_SPR_DEC;
			SNDK_OAM1.t[idx] = acc+SNDK_SPR_SIZET;
		}
	}else
	{
		if( attribute & OAM_XFLIP)
		{
			SNDK_OAM1.t[idx] = tile;
			SNDK_OAM0.t[idx] = acc+SNDK_SPR_SIZET;
			SNDK_OAM3.t[idx] = tile+SNDK_SPR_DEC;
			SNDK_OAM2.t[idx] = acc+SNDK_SPR_SIZET;
		}else
		{
			SNDK_OAM0.t[idx] = tile;
			SNDK_OAM1.t[idx] = acc+SNDK_SPR_SIZET;
			SNDK_OAM2.t[idx] = tile+SNDK_SPR_DEC;
			SNDK_OAM3.t[idx] = acc+SNDK_SPR_SIZET;
		}
	}
	
	SNDK_OAM0.a[idx] = attribute;
	SNDK_OAM1.a[idx] = acc;
	SNDK_OAM2.a[idx] = acc;
	SNDK_OAM3.a[idx] = acc;
	
	 uint16 indexh;
	
	SNDK_Sprite.oam = idx + 16;
	
	indexh = acc>>4;
	
	if( position.x &! 0xFF00)
	{
		flag = flag&0xAA;
	}
	
	
	SNDK_OAMH[indexh] = flag;
}

void SNDK_SpriteDrawMeta2x2(uint16 position.x,uint8 position.y,uint8 tile,uint8 attribute,uint8 flag)
{
	
	idx = SNDK_Sprite.oam;
	
	SNDK_OAM0.x[idx] = position.x;
	SNDK_OAM2.x[idx] = acc;
	SNDK_OAM1.x[idx] = acc+SNDK_SPR_SIZE;
	SNDK_OAM3.x[idx] = acc;
	
	SNDK_OAM0.y[idx] = position.y;
	SNDK_OAM1.y[idx] = acc;
	SNDK_OAM2.y[idx] = acc+SNDK_SPR_SIZE;
	SNDK_OAM3.y[idx] = acc;
	
	SNDK_OAM0.t[idx] = tile;
	SNDK_OAM1.t[idx] = acc+SNDK_SPR_SIZET;
	SNDK_OAM2.t[idx] = tile+SNDK_SPR_DEC;
	SNDK_OAM3.t[idx] = acc+SNDK_SPR_SIZET;
	
	if( attribute & OAM_YFLIP)
	{
		if( attribute & OAM_XFLIP)
		{
			SNDK_OAM3.t[idx] = tile;
			SNDK_OAM2.t[idx] = acc+SNDK_SPR_SIZET;
			SNDK_OAM1.t[idx] = tile+SNDK_SPR_DEC;
			SNDK_OAM0.t[idx] = acc+SNDK_SPR_SIZET;
		}else
		{
			SNDK_OAM2.t[idx] = tile;
			SNDK_OAM3.t[idx] = acc+SNDK_SPR_SIZET;
			SNDK_OAM0.t[idx] = tile+SNDK_SPR_DEC;
			SNDK_OAM1.t[idx] = acc+SNDK_SPR_SIZET;
		}
	}else
	{
		if( attribute & OAM_XFLIP)
		{
			SNDK_OAM1.t[idx] = tile;
			SNDK_OAM0.t[idx] = acc+SNDK_SPR_SIZET;
			SNDK_OAM3.t[idx] = tile+SNDK_SPR_DEC;
			SNDK_OAM2.t[idx] = acc+SNDK_SPR_SIZET;
		}else
		{
			SNDK_OAM0.t[idx] = tile;
			SNDK_OAM1.t[idx] = acc+SNDK_SPR_SIZET;
			SNDK_OAM2.t[idx] = tile+SNDK_SPR_DEC;
			SNDK_OAM3.t[idx] = acc+SNDK_SPR_SIZET;
		}
	}
	
	SNDK_OAM0.a[idx] = attribute;
	SNDK_OAM1.a[idx] = acc;
	SNDK_OAM2.a[idx] = acc;
	SNDK_OAM3.a[idx] = acc;
	
	 uint16 indexh;
	
	SNDK_Sprite.oam = idx + 16;
	
	indexh = acc>>4;
	
	if( position.x &! 0xFF00)
	{
		flag = flag&0xAA;
	}
	
	
	SNDK_OAMH[indexh] = flag;
}

void SNDK_SpriteDrawMeta2x2H(uint16 position.x,uint8 position.y,uint8 tile,uint8 attribute,uint8 flag)
{
	
	idx = SNDK_Sprite.oam;
	
	SNDK_OAM0.x[idx] = position.x;
	SNDK_OAM2.x[idx] = acc;
	SNDK_OAM1.x[idx] = acc+SNDK_SPR_SIZE2;
	SNDK_OAM3.x[idx] = acc;
	
	SNDK_OAM0.y[idx] = position.y;
	SNDK_OAM1.y[idx] = acc;
	SNDK_OAM2.y[idx] = acc+SNDK_SPR_SIZE2;
	SNDK_OAM3.y[idx] = acc;
	
	SNDK_OAM0.t[idx] = tile;
	SNDK_OAM1.t[idx] = acc+SNDK_SPR_SIZET2;
	SNDK_OAM2.t[idx] = tile+SNDK_SPR_DEC2;
	SNDK_OAM3.t[idx] = acc+SNDK_SPR_SIZET2;
	
	if( attribute & OAM_YFLIP)
	{
		if( attribute & OAM_XFLIP)
		{
			SNDK_OAM3.t[idx] = tile;
			SNDK_OAM2.t[idx] = acc+SNDK_SPR_SIZET2;
			SNDK_OAM1.t[idx] = tile+SNDK_SPR_DEC2;
			SNDK_OAM0.t[idx] = acc+SNDK_SPR_SIZET2;
		}else
		{
			SNDK_OAM2.t[idx] = tile;
			SNDK_OAM3.t[idx] = acc+SNDK_SPR_SIZET2;
			SNDK_OAM0.t[idx] = tile+SNDK_SPR_DEC2;
			SNDK_OAM1.t[idx] = acc+SNDK_SPR_SIZET2;
		}
	}else
	{
		if( attribute & OAM_XFLIP)
		{
			SNDK_OAM1.t[idx] = tile;
			SNDK_OAM0.t[idx] = acc+SNDK_SPR_SIZET2;
			SNDK_OAM3.t[idx] = tile+SNDK_SPR_DEC2;
			SNDK_OAM2.t[idx] = acc+SNDK_SPR_SIZET2;
		}else
		{
			SNDK_OAM0.t[idx] = tile;
			SNDK_OAM1.t[idx] = acc+SNDK_SPR_SIZET2;
			SNDK_OAM2.t[idx] = tile+SNDK_SPR_DEC2;
			SNDK_OAM3.t[idx] = acc+SNDK_SPR_SIZET2;
		}
	}
	
	SNDK_OAM0.a[idx] = attribute;
	SNDK_OAM1.a[idx] = acc;
	SNDK_OAM2.a[idx] = acc;
	SNDK_OAM3.a[idx] = acc;
	
	 uint16 indexh;
	
	SNDK_Sprite.oam = idx + 16;
	
	indexh = acc>>4;
	
	if( position.x &! 0xFF00)
	{
		flag = flag&0xAA;
	}
	
	
	SNDK_OAMH[indexh] = flag;
}