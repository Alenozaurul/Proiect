#ifndef __ACTION_H__
#define __ACTION_H__

#include "spaceships.h"

void playerMovement( Player *player, const unsigned char *keys );
void playerShooting( Player *player, const unsigned char *keys, int *reload );
void playerShoot( Player *player );

#endif
