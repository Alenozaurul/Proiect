#include<stdbool.h>
#include<stdio.h>
#include<SDL2/SDL.h>

#include "headers/gamemodes.h"



int gamemode = -1;


int main( int argc, char **argv )
{	
	system("cat begin.txt");
	
	while( gamemode )
	{
		printf("Gamemode: ");
		scanf("%i", &gamemode);
		printf("\n");
		
		switch( gamemode )
		{
			case 1:
				startGM1();
				break;

			case 2:
				startGM2();
				break;
		}


	}

	return 0;
}

