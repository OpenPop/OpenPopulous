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

#include "Language.h"

int		buffer_size = 0;
wchar_t	*lang_buffer = NULL;
int		lang_offsets[MAX_STRINGS];
int		num_strings = 0;

void FindOffsets();

bool LoadLanguage()
{
	FILE *lFile;
	char *path;
	
	path = "language\\lang00.dat";
	//path = "language\\lang00.dat";
	lFile = fopen(path, "rb");
	if (lFile != NULL) {
		//Get file size
		fseek(lFile, 0, SEEK_END);
		buffer_size = ftell(lFile);

		//Allocate new memory for the buffer
		lang_buffer = (wchar_t*)malloc(buffer_size);

		//Read the file into the buffer
		rewind(lFile);
		fread(lang_buffer, buffer_size, 1, lFile);

		//Close the file
		fclose(lFile);

		//Find all the string offsets
		FindOffsets();

		//Return successfully
		return true;
	}

	//Unable to load language file
	return false;
}

void FreeLanguage()
{
	//Free the buffer
	if (lang_buffer != NULL)
		free(lang_buffer);
}

void FindOffsets()
{
	num_strings = 0;
	memset(lang_offsets, 0, MAX_STRINGS * 4);

	//First string at offset 0
	lang_offsets[0] = 0;
	num_strings++;

	for (int i = 0; i < buffer_size / 2; i++) {
		if (lang_buffer[i] == 0) {
			lang_offsets[num_strings] = (i * 2) + 2;
			num_strings++;
		}
	}
}

wchar_t *GetString(int index)
{
	return &lang_buffer[lang_offsets[index] / 2];
}