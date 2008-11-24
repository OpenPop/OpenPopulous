/********************************************************************** 
  This file is part of OpenPop

  OpenPop is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  any later version.

  OpenPop is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with OpenPop.  If not, see <http://www.gnu.org/licenses/>.
***********************************************************************/

#include <cstdlib>
#include <cstdio>
#include <cstring>

#include <sdl/sdl.h>

#include "Sprites.h"
#include "Video.h"

PopPalette *pal;
SpriteCollection *hfx, *hspr;

bool LoadSpriteCollection(const char *path, SpriteCollection *collection);
void FreeSpriteCollection(SpriteCollection *collection);
bool LoadPopPalette(const char *path, PopPalette *palette);

void LoadSpriteCollections()
{
	pal = new PopPalette();
	hfx  = new SpriteCollection();
	hspr = new SpriteCollection();

	LoadPopPalette("data\\pal0-c.dat", pal);
	LoadSpriteCollection("data\\hfx0-0.dat", hfx);
	LoadSpriteCollection("data\\hspr0-0.dat", hspr);
}

void FreeSpriteCollections()
{
	FreeSpriteCollection(hfx);
	FreeSpriteCollection(hspr);
}

bool LoadSpriteCollection(const char *path, SpriteCollection *collection)
{
	FILE *sFile;
	int bsize;
	char *buffer;

	sFile = fopen(path, "rb");
	if (sFile == NULL) {
		//Unable to load sprite collection file
		return false;
	}

	//Get file size
	fseek(sFile, 0, SEEK_END);
	bsize = ftell(sFile);

	//Allocate new memory for the buffer
	buffer = (char*)malloc(bsize);

	//Read the file into the buffer
	rewind(sFile);
	fread(buffer, bsize, 1, sFile);

	//Close the file
	fclose(sFile);

	//Check file signature
	if (*((unsigned int*)(&buffer[0])) != 0x42465350)
		return false;

	memset(collection, 0, sizeof(SpriteCollection));

	//Get number of sprites
	collection->num_sprites = *((unsigned int*)(&buffer[4]));

	//Fill in sprite header details
	collection->widths = new unsigned short[collection->num_sprites];
	collection->heights = new unsigned short[collection->num_sprites];
	collection->offsets = new unsigned int[collection->num_sprites];

	for (int i = 0; i < collection->num_sprites; i++) {
		collection->widths[i] = *((unsigned short*)(&buffer[(i * 8) + 8]));
		collection->heights[i] = *((unsigned short*)(&buffer[(i * 8) + 10]));
		collection->offsets[i] = *((unsigned int*)(&buffer[(i * 8) + 12]));
	}

	collection->buffer_size = bsize;
	collection->buffer = buffer;

	//Return successfully
	return true;
}

void FreeSpriteCollection(SpriteCollection *collection)
{
	if (collection->buffer != NULL)
		delete collection->buffer;

	if (collection->widths != NULL)
		delete collection->widths;

	if (collection->heights != NULL)
		delete collection->heights;

	if (collection->offsets != NULL)
		delete collection->offsets;

	memset(collection, 0, sizeof(SpriteCollection));
}

bool LoadPopPalette(const char *path, PopPalette *palette)
{
	FILE *pFile;
	int bsize;
	char *buffer;

	pFile = fopen(path, "rb");
	if (pFile == NULL) {
		//Unable to load palette file
		return false;
	}

	//Get file size
	fseek(pFile, 0, SEEK_END);
	bsize = ftell(pFile);

	//Check for the correct length
	if (bsize != sizeof(PopPalette)) {
		return false;
	}

	//Read the file into the buffer
	rewind(pFile);
	fread(palette, bsize, 1, pFile);

	//Close the file
	fclose(pFile);

	//Return successfully
	return true;
}

void DrawSprite(int destX, int destY, const SpriteCollection *collection, int sprite)
{
	//Get sprite info.
	int offset = collection->offsets[sprite];
	int width = collection->widths[sprite];
	int height = collection->heights[sprite];

	//Draw sprite with transparancy
	char *sbuffer = collection->buffer;
	int pos = offset;
	signed char counter;
	for (int y = destY; y < destY + height; y++) {
		//Set x to the start of destX
		int x = destX;

		//Loop through the pixels
		do {
			//Read the counter byte
			counter = sbuffer[pos];

			//Increment pos
			pos++;

			//Check if counter is positive
			if (counter > 0) {
				for (int i = 0; i < counter; i++) {
					//Draw so many of the next pixels
					DrawPixel(x, y, pal->entry[(unsigned char)sbuffer[pos]]);

					//Increment position
					pos++;

					//Add a pixel onto x
					x++;
				}
			} else if (counter < 0) {
				//Counter is negative therfore a transparant line of pixels
				x += -counter;
			}
			
			//Reloop if counter is not equal to 0
		} while (counter != 0);
	}
}