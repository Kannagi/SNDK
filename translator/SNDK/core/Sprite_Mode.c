

void MC_SNDK_SpriteEngineDrawMode0 (){
	
	SNDK_SPRITE.visible[idx]  = 0;
	
	
	acc = posy + 0xC020;
	if( acc & 0x3F00)
	{
		SNDK_Sprite.oam += 0x4	;
		asm "rts";
	}
	
	acc = posx + 0xC000;
	acc += tmp;
	if( acc ?= 0)
	{
		acc = SNDK_Sprite.oam>>2;
		tmp = acc&3;
		
		if( tmp == 0)
		{
			posxh |= 0x01;
		}
		
		if( tmp == 1)
		{
			posxh |= 0x04;
		}
		
		if( tmp == 2)
		{
			posxh |= 0x10;
		}
		
		if( tmp == 3)
		{
			posxh |= 0x40;
		}
		

	}else
	{
		acc -= tmp;
		if( acc & 0x3F00)
		{
			SNDK_Sprite.oam += 0x4	;
			asm "rts";
		}
	}	
	draw = SNDK_SPRITE.draw[idx] ;
	SNDK_SPRITE.visible[idx]  = 1;
	acc = SNDK_Sprite.oam;
	idx = acc;
	indexh = acc>>4;
	
	
	
	
	if( draw != 0)
	{
		
		SNDK_Sprite.oam += 0x4;
		asm "rts";
		
	}
	
	
	SNDK_OAM0.x[idx] = posx;
	SNDK_OAM0.y[idx] = posy;
	SNDK_OAM0.t[idx] = tile;
	SNDK_OAM0.a[idx] = attribute;
	
	
	SNDK_OAMH[indexh] |= posxh;
}


void SNDK_SpriteEngineDrawMode0()
{
	 uint16 posx,posy;
	 uint8 tile,attribute,draw,draw2;
	 uint16 posxh,indexh;
	 uint16 tmp,oldx;
	
	
	
	tmp = SNDK_SPR_SIZE&0xFF;
	idx = oldx;
	
	posxh = SNDK_SPRITE.flag[idx];
	
	MC_SNDK_SpriteEngineDrawMode0;
	
	
	SNDK_Sprite.oam += 0x4	;
	asm "rts";
}

void SNDK_SpriteEngineDrawMode0z()
{
	 uint16 posx,posy;
	 uint8 tile,attribute,draw,draw2;
	 uint16 posxh,indexh;
	 uint16 tmp,oldx;
	
	
	
	tmp = SNDK_SPR_SIZE2&0xFF;
	idx = oldx;
	
	posxh = SNDK_SPRITE.flag[idx] |  0xAA;
	
	MC_SNDK_SpriteEngineDrawMode0;
	
	
	SNDK_Sprite.oam += 0x4	;
	asm "rts";
}




void SNDK_SpriteEngineDraw()
{
	 uint16 posx,posy;
	 uint8 tile,attribute;
	 uint16 posxh,indexh;
	 uint16 fptr,oldx;
	
	
	
	idx = oldx;
	
	SNDK_SPRITE.visible[idx]  = 0;
	acc = posy + 0xC020;
	if( acc & 0x3F00)
	{
		return;
	}
	
	posxh = 0;

	acc = posx + 0xC010;
	if( acc ?= 0)
	{
		posxh = 0x11;
	}else
	{
		acc += 0x10;
		if( acc ?= 0)
		{
			posxh = 0x55;
		}else
		{
			acc -= 0x20;
			if( acc & 0x3F00)
			{
				return;
			}
			
		}

	}
	
	SNDK_SPRITE.visible[idx]  = 1;
	idx = SNDK_Sprite.oam;
	indexh = idx>>4;
	
	SNDK_Sprite.oam += 0x10	;

	
	
	
	SNDK_OAM0.x[idx] = posx;
	SNDK_OAM0.y[idx] = posy;
	SNDK_OAM0.t[idx] = tile;
	SNDK_OAM0.a[idx] = attribute;
	
	
	
	
	SNDK_OAMH[indexh] = posxh;
	
	
	
}

void MC_SNDK_SpriteEngineDrawModeTile (){
	

	if( attribute & OAM_XFLIP)
	{
		acc = .arg1&0xF;
		tmpx = acc <<4;
		
		tmpy =  .arg1&0xF0;
		
		acc = posx - tmpx;
		if( acc & 0xFF00)
		{
			
			.arg3 |= .arg4;
		}
		
		SNDK_OAM0.x[idx] = posx - tmpx;
	}
	else
	{
		
		acc = .arg1&0xF;
		tmpx = acc;
		acc = 5 - tmpx;
		tmpx = acc <<4;
		tmpx -= 0x40;
		
		acc = posx - tmpx;
		if( acc & 0xFF00)
		{
			
			.arg3 |= .arg4;
		}
		
		tmpy =  .arg1&0xF0;
		
		
		SNDK_OAM0.x[idx] = posx - tmpx;
	}
	
	if( .arg1 == 0xFF)
	{
		SNDK_OAM0.y[idx] = 0xE0;
	}
	else
	{
		SNDK_OAM0.y[idx] = posy + tmpy;
	}
	
	
	SNDK_OAM0.t[idx] = tile + .arg2;
	SNDK_OAM0.a[idx] = attribute;
	
	
	idx += 4;

	
}



void SNDK_SpriteEngineDrawModeTile()
{
	 uint16 posx,posy;
	 uint8 tile,attribute,draw,draw2;
	 uint16 posxh,indexh;
	 uint16 fptr,oldx;
	
	 uint8 ctile1,ctile2,ctile3,ctile4;
	 uint8 ctile5,ctile6,ctile7,ctile8;
	 uint8 ctile9,ctile10,ctile11,ctile12;
	 uint8 ctile13,ctile14,ctile15,ctile16;
	
	 uint16 tmpx,tmpy;
	 uint16 list;
	 uint8 flag1,flag2,flag3,flag4;
	
	
	
	acc = posx;
	if( acc & 0x2000)
	{
		if( acc < 0x3F80)
		{
			asm "rts";
		}
	}
	else
	{
		if( acc >= 0x180)
		{
			asm "rts";
		}
	}

	
	tmpx = 0;
	idx = oldx;
	list = SNDK_SPRITE.add[idx]>>7;
	acc = SNDK_SPRITE.bank[idx]&0xF;
	acc = acc << 8;
	list += acc;
	
	SNDK_SPRITE.visible[idx]  = 1;
	idx = SNDK_Sprite.oam;
	indexh = idx>>4;
	
	SNDK_Sprite.oam += 0x40	;
	
	
	
	
	flag1 = 0;
	flag2 = 0;
	flag3 = 0;
	flag4 = 0;
	
	SAVEX;
	idx = list;
	
	ctile1 = [SPRITE_TILE,idx];
	idx+=1;
	
	ctile2 = [SPRITE_TILE,idx];
	idx+=1;
	
	ctile3 = [SPRITE_TILE,idx];
	idx+=1;
	
	ctile4 = [SPRITE_TILE,idx];
	idx+=1;
	
	ctile5 = [SPRITE_TILE,idx];
	idx+=1;
	
	ctile6 = [SPRITE_TILE,idx];
	idx+=1;
	
	ctile7 = [SPRITE_TILE,idx];
	idx+=1;
	
	ctile8 = [SPRITE_TILE,idx];
	idx+=1;
	
	ctile9 = [SPRITE_TILE,idx];
	idx+=1;
	
	ctile10 = [SPRITE_TILE,idx];
	idx+=1;
	
	ctile11 = [SPRITE_TILE,idx];
	idx+=1;
	
	ctile12 = [SPRITE_TILE,idx];
	idx+=1;
	
	ctile13 = [SPRITE_TILE,idx];
	idx+=1;
	
	ctile14 = [SPRITE_TILE,idx];
	idx+=1;
	
	ctile15 = [SPRITE_TILE,idx];
	idx+=1;
	
	ctile16 = [SPRITE_TILE,idx];
	idx+=1;
	
	RESTOREX;
	
	
	MC_SNDK_SpriteEngineDrawModeTile ctile1,0,flag1,0x01;
	MC_SNDK_SpriteEngineDrawModeTile ctile2,2,flag1,0x04;
	MC_SNDK_SpriteEngineDrawModeTile ctile3,4,flag1,0x10;
	MC_SNDK_SpriteEngineDrawModeTile ctile4,6,flag1,0x40;
	
	MC_SNDK_SpriteEngineDrawModeTile ctile5,8,flag2,0x01;
	MC_SNDK_SpriteEngineDrawModeTile ctile6,10,flag2,0x04;
	MC_SNDK_SpriteEngineDrawModeTile ctile7,12,flag2,0x10;
	MC_SNDK_SpriteEngineDrawModeTile ctile8,14,flag2,0x40;
	
	MC_SNDK_SpriteEngineDrawModeTile ctile9,0x20,flag3,0x01;
	MC_SNDK_SpriteEngineDrawModeTile ctile10,0x22,flag3,0x04;
	MC_SNDK_SpriteEngineDrawModeTile ctile11,0x24,flag3,0x10;
	MC_SNDK_SpriteEngineDrawModeTile ctile12,0x26,flag3,0x40;
	
	MC_SNDK_SpriteEngineDrawModeTile ctile13,0x28,flag4,0x01;
	MC_SNDK_SpriteEngineDrawModeTile ctile14,0x2A,flag4,0x04;
	MC_SNDK_SpriteEngineDrawModeTile ctile15,0x2C,flag4,0x10;
	MC_SNDK_SpriteEngineDrawModeTile ctile16,0x2E,flag4,0x40;
	
	
	idx = indexh;
	SNDK_OAMH[idx] = flag1;
	idx+=1;
	
	SNDK_OAMH[idx] = flag2;
	idx+=1;
	
	SNDK_OAMH[idx] = flag3;
	idx+=1;
	
	SNDK_OAMH[idx] = flag4;
	
	
	
	
	asm "rts";
	
}
