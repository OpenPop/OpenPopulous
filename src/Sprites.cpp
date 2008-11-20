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

#include "Sprites.h"

bool LoadSpriteCollection(const char *path, SpriteCollection *collection);
void FreeSpriteCollection(SpriteCollection *collection);

void LoadSpriteCollections()
{
	SpriteCollection c;
	char *path = "C:\\Users\\Ted\\Documents\\Populous\\OpenPop\\bin\\data\\hfx0-0.dat";
	LoadSpriteCollection(path, &c);

	FreeSpriteCollection(&c);
}

void FreeSpriteCollections()
{
	
}

bool LoadSpriteCollection(const char *path, SpriteCollection *collection)
{
	FILE *sFile;
	int bsize;
	char *buffer;

	sFile = fopen(path, "r");
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
	fseek(sFile, 0, SEEK_SET);
	fread(buffer, bsize, 1, sFile);

	//Close the file
	fclose(sFile);

	//Check file signature
	if (*((unsigned int*)(&buffer[0])) != 0x42465350)
		return false;

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