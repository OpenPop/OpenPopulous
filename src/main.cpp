#include <cstdio>

#include "Language.h"
#include "Sprites.h"

int main()
{
	LoadLanguage();
	LoadSpriteCollections();

	for (int i = 0; i < 1000; i++) {
		wprintf(L"%d. %s\n", i, GetString(i));
	}

	return 0;
}