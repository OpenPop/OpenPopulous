#include <stdio.h>

#include "Game.h"
#include "Map.h"

Game::Game()
{
	
}

Game::~Game()
{

}

void Game::LoadMap(char *filename)
{
	char *buffer;
	int fsize;
	FILE *file;

	file = fopen(filename, "rb");
	if (file > 0) {
		//Get file length
		fseek(file, 0, SEEK_END);
		fsize = ftell(file);
		rewind(file);

		//Get buffer
		buffer = (char*)malloc(fsize);
		if (!fread(buffer, fsize, 1, file) > 0) {
			//Error loading
			fclose(file);
			return;
		}
		
		LoadOldMapFormat(buffer, fsize);
		free(buffer);
		fclose(file);
	} else {
		//Error loading
		return;
	}
}

void Game::LoadNewMapFormat(char *buffer, int length)
{

}

void Game::LoadOldMapFormat(char *buffer, int length)
{
	int pos = 0;

	Map *map = new Map();

	//Setup land size, array and then copy the heights over
	map->mSize = 128;
	map->mLandHeight = new unsigned short[128 * 128];
	memcpy(map->mLandHeight, buffer, 128 * 128 * 2);
}