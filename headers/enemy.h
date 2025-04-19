#ifndef __ENEMY_H__
#define __ENEMY_H__

#include "spaceships.h"

void spawnEnemy( Enemy *enemy, int *respawn );
void enemyShooting( Enemy *enemy, int *reload_enemy );
void enemyShoot( Enemy *enemy, int nr );

#endif
