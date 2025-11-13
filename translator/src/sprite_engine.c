

void sprite_engine()
{
	
	
	
	
	
	SNDK_memcopy( SNDK_PALSPR0,HERO_PAL,0x40);
	
	SNDK_SendCGRAM 0x00,SNDK_PALBG0,0x200;
	
	
	
	 uint16 pfunc;
	pfunc =+ &SNDK_SpriteEngineDrawMode0z();
	 SNDK_Init_SpriteList( SPR_INDEX_0,0,0x00,(OAM_PAL0 | OAM_PRIO2),pfunc);
	 SNDK_Init_SpriteList( SPR_INDEX_1,1,0x04,(OAM_PAL1 | OAM_PRIO2),pfunc);

	
	idx = SPR_INDEX_0;
	SNDK_SPRITE.x[idx] = 0x80;
	SNDK_SPRITE.y[idx] = 0x80;
	SNDK_SPRITE.index[idx]  = 52;
	
	idx = SPR_INDEX_1;
	SNDK_SPRITE.x[idx] = 0x100;
	SNDK_SPRITE.y[idx] = 0x100;
	SNDK_SPRITE.index[idx]  = 52;
	
	
	
	 uint8 fade,anim;
	fade = 0;
	
	
	uint16 flag;
	flag = (OAM_PAL0 | OAM_PRIO2);
	
	TM = (SNDK_OBJ | SNDK_BG3);
	
	do
	{
		 SNDK_Sprite();
		
		 SNDK_SpriteEngine(0,2,1);
		
		
		idx = SPR_INDEX_0;
		SNDK_SPRITE.vx[idx] = 0;
		SNDK_SPRITE.vy[idx] = 0;
		
		anim = 0;
		
		if( SNDK_Joypad.pad1h & SNDK_PAD_RIGHT)
		{
			SNDK_SPRITE.vx[idx] = 3;
			SNDK_SPRITE.index[idx]  = 26;
			flag = (OAM_PAL0 | OAM_PRIO2);
			anim = 1;
		}
		
		if( SNDK_Joypad.pad1h & SNDK_PAD_LEFT)
		{
			SNDK_SPRITE.vx[idx] = (-3);
			SNDK_SPRITE.index[idx]  = 26;
			flag = (OAM_PAL0 | OAM_PRIO2 | OAM_XFLIP);
			anim = 1;
		}
		
		if( SNDK_Joypad.pad1h & SNDK_PAD_UP)
		{
			SNDK_SPRITE.vy[idx] = (-3);
			SNDK_SPRITE.index[idx]  = 0;
			anim = 1;
		}
		
		if( SNDK_Joypad.pad1h & SNDK_PAD_DOWN)
		{
			SNDK_SPRITE.vy[idx] = 3;
			SNDK_SPRITE.index[idx]  = 52;
			anim = 1;
		}
		
		
		SNDK_SPRITE.a[idx] = flag;
		
		
		if( anim == 0)
		{
			SNDK_SPRITE.ianim[idx] = 0;
		}
		
		
		if( SNDK_Joypad.pad1h & SNDK_PAD_SELECT)
		{
			fade = 1;
		}
		
		 SNDK_Fade( 6,fade);
		if( acc == 1)
		{
			if( fade == 1)
			{
				
				TM = (SNDK_BG3);
				return;
			}
		}
		 SNDK_WaitVBlank();
	}
	while( 1 == 1);
}