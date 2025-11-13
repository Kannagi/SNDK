
void SNDK_BulletInit(uint16 n)
{
	
	
	idy = n;
	idx = 0;
	do
	{	
		acc = 0;
		SNDK_Bullet.vx[idx] = acc;
		SNDK_Bullet.vy[idx] = acc;
		SNDK_Bullet.t[idx] = acc;
		SNDK_Bullet.x[idx] = acc;
		
		SNDK_Bullet.y[idx] = 0xE000;
		
		SNDK_Bullet.usable1[idx] = 1;
		SNDK_Bullet.usable2[idx] = 1;
		
		idx += 2;
	}
	while(-- idy == 0);

	
	
}


void SNDK_BulletEngine1()
{
	
	SNDK_Bullet.usable1[0]  = 1;
	do
	{	
		 SNDK_BulletOut1();

		idx += 2;
		
	}
	while(-- idy == 0);
	
}

void SNDK_BulletEngine2()
{
	SNDK_Bullet.usable2[0]  = 1;
	do
	{	
		 SNDK_BulletOut2();

		idx += 2;
		
	}
	while(-- idy == 0);
}


void SNDK_BulletEngine(uint16 n1,uint16 n2)
{
	 uint16 oam,xuse;
	
	
	
	oam = SNDK_Sprite.oam;
	
	
	
	if( n2 != 0)
	{
		
		xuse = 0;
		idy = n2;
		idx = n1<<1;
		 SNDK_BulletEngine2();
		
		SNDK_Bullet.usable2[xuse]  = 1;
		SNDK_Sprite.oam = oam;
		
	}
	
	
	if( n1 != 0)
	{
		
		xuse = 0;
		idy = n1;
		idx = 0;
		 SNDK_BulletEngine1();
		
		SNDK_Bullet.usable1[xuse]  = 1;
		SNDK_Sprite.oam = oam;
		
	}
	
	
	
	
	
	
	
	
	
	return;
}

void SNDK_BulletHitboxSet(uint16 beg,uint16 n,uint16 x,uint16 y,uint16 w,uint16 h)
{
	uint16 begin,count;
	uint16 rect.x,rect.y,rect.w,rect.h;
	
	begin = beg<<1;
	count = n;
	
	
	if( x & 0x2000)
	{
		acc = x & 0xFF;
		acc = acc ^ 0xFF;
		w -= acc;
		x = 0;
	}
	
	
	rect.x = x;
	rect.y = y;
	rect.w = x+w;
	rect.h = y+h;
	
	if( rect.w & 0x1F00)
	{
		rect.w = 255;
	}
	
}

void SNDK_BulletHitbox()
{
	 uint16 x,y;
	 uint16 rect.x,rect.y,rect.w,rect.h;
	
	rect.x = SNDK_BulletHitboxSet.rect.x;
	rect.y = SNDK_BulletHitboxSet.rect.y;
	rect.w = SNDK_BulletHitboxSet.rect.w;
	rect.h = SNDK_BulletHitboxSet.rect.h;
	
	idy = SNDK_BulletHitboxSet.count;
	idx = SNDK_BulletHitboxSet.begin;
	idx+=1;
	do
	{	y = SNDK_Bullet.y[idx]
		if( acc != 0xE0)
		{
			acc = SNDK_Bullet.x[idx];
			if( acc >= rect.x)
			{
				if( acc < rect.w)
				{
					x = acc;
					acc = y;
					if( acc >= rect.y)
					{
						if( acc < rect.h)
						{
							
							idx -=1;
							SNDK_Bullet.y[idx] = 0xE000;
							
							acc = 0;
							SNDK_Bullet.x[idx] =acc;
							SNDK_Bullet.vx[idx] = acc;
							SNDK_Bullet.vy[idx] = acc;

							
							return 1;
						}
					}
				}
			}
		}
	
		idx += 2;
	}
	while(-- idy == 0);
	
	return 0;
}

void SNDK_BulletOut1()
{
	 uint16 oam,xuse,tmp;
	 uint8 posx,posx2;
	 uint8 posy,posy2;
	 uint8 tile,attribute;
	
	
	
	SNDK_Bullet.x[idx]  +=  SNDK_Bullet.vx[idx];
	posx = acc;
	acc = acc & 0xF800;
	if( acc == 0xF800)
	{
		acc = 0;
		SNDK_Bullet.x[idx] = acc;
		SNDK_Bullet.vx[idx] = acc;
		SNDK_Bullet.vy[idx] = acc;
		
		SNDK_Bullet.y[idx] = 0xE000;
	}
	
	SNDK_Bullet.y[idx]  +=  SNDK_Bullet.vy[idx];
	posy = acc;
	acc = acc & 0xF000;
	if( acc == 0xF000)
	{
		acc = 0;
		SNDK_Bullet.x[idx] = acc;
		SNDK_Bullet.vx[idx] = acc;
		SNDK_Bullet.vy[idx] = acc;
		
		SNDK_Bullet.y[idx] = 0xE000;
	}
	
	tile = SNDK_Bullet.t[idx] ;
	
	tmp = idx;
	asm "phx";
	
	if( posy == 0xE000)
	{
		idx = xuse;
		SNDK_Bullet.usable1[idx] = tmp ;
		idx+=2;
		xuse = idx;
		
		asm "plx";
		oam += 4;
		
		return;
		
	}
	
	acc = oam;
	idx = acc;
	oam = acc + 4;

	SNDK_OAM0.t[idx] = tile;
	
	
	SNDK_OAM0.x[idx] = posx2;
	SNDK_OAM0.y[idx] = posy2;

	
	asm "plx";
}

void SNDK_BulletOut2()
{
	 uint16 oam,xuse,tmp;
	 uint8 posx,posx2;
	 uint8 posy,posy2;
	 uint8 tile,attribute;
	
	
	
	
	SNDK_Bullet.x[idx]  +=  SNDK_Bullet.vx[idx];
	posx = acc;
	acc = acc & 0xF800;
	if( acc == 0xF800)
	{
		acc = 0;
		SNDK_Bullet.x[idx] = acc;
		SNDK_Bullet.vx[idx] = acc;
		SNDK_Bullet.vy[idx] = acc;
		
		SNDK_Bullet.y[idx] = 0xE000;
	}
	
	SNDK_Bullet.y[idx]  +=  SNDK_Bullet.vy[idx];
	posy = acc;
	acc = acc & 0xF000;
	if( acc == 0xF000)
	{
		acc = 0;
		SNDK_Bullet.x[idx] = acc;
		SNDK_Bullet.vx[idx] = acc;
		SNDK_Bullet.vy[idx] = acc;
		
		SNDK_Bullet.y[idx] = 0xE000;
	}
	
	tile = SNDK_Bullet.t[idx] ;
	
	tmp = idx;
	asm "phx";

	if( posy == 0xE000)
	{
		idx = xuse;
		SNDK_Bullet.usable2[idx] = tmp ;
		idx+=2;
		xuse = idx;
		
		asm "plx";
		oam += 4;
		
		return;
		
	}
	
	acc = oam;
	idx = acc;
	oam = acc + 4;

	SNDK_OAM0.t[idx] = tile;
	
	
	SNDK_OAM0.x[idx] = posx2;
	SNDK_OAM0.y[idx] = posy2;
	
	
	asm "plx";
}