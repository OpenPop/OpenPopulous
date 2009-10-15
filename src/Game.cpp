#include <stdio.h>
#include "Game.h"
#include "Map.h"
#include "Object.h"
#include "Unit.h"

Game* gGame;

Game::Game()
{
	LoadMap("levels\\levl2131.dat");
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

	mMap = new Map();

	//Setup land size, array and then copy the heights over
	mMap->InitMap(128);

	unsigned short *lb = (unsigned short*)(buffer);
	
	for (int y = 0; y < 128; y++) {
		for (int x = 0; x < 128; x++) {
			mMap->SetLandHeight(x, y, lb[(y * 128) + x]);
		}
	}

	pos = 0x14043;

	for (int i = 0; i < 2000; i++) {
		char type = buffer[pos];
		char group = buffer[pos + 1];
		

		if(group == 1){
			Unit* unit = new Unit(type);

			unit->mTribe = (unsigned char)buffer[pos + 2];
			unit->mX =     (unsigned char)buffer[pos + 4];
			unit->mZ =     (unsigned char)buffer[pos + 6];

			mMap->AddObject(unit);
		}

		pos += 55;
	}
}

void Game::Update()
{
	mMap->Update();
}