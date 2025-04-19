#include "headers/enemy.h"

void spawnEnemy( Enemy *enemy, int *respawn )
{
	if( *respawn <= 0 )
	{
		for( int i = 0; i < 30; ++i )
		{
			if( enemy[i].body.w == 0 )
			{
				enemy[i].body.w = 40;
                		enemy[i].body.h = 40;
                		enemy[i].body.x = 20 + ( rand() % 984 );
                		enemy[i].body.y = 0;
				break;
			}
		}
		*respawn = 150;
	}
	else
	{
		--( *respawn);
	}
}


void enemyShooting( Enemy *enemy, int *reload_enemy )
{
	for( int i = 0; i < 30; ++i )
	{
		if( enemy[i].body.w > 0 && reload_enemy[i] <= 0 )
		{
			reload_enemy[i] = 200;
			enemyShoot( enemy, i );
		}
		else if( enemy[i].body.w > 0 )
		{
			--( reload_enemy[i] );
		}
	}
}

void enemyShoot( Enemy *enemy, int nr )
{

	for( int i = 0; i < 30; ++i )
	{
		if( enemy[nr].bullets[i].w == 0 )
		{
			enemy[nr].bullets[i].w = 10;
			enemy[nr].bullets[i].h = 10;
			enemy[nr].bullets[i].x = enemy[nr].body.x + enemy[nr].body.w / 2;
			enemy[nr].bullets[i].y = enemy[nr].body.y + enemy[nr].body.h / 2;
			break;
		}
	}
}



