#include <iostream>
#include <fstream>
#include "PaletteFile.h"

using namespace std;
using namespace Graphics;

PaletteFile::PaletteFile(string filename)
{
	ifstream fs;
	fs.open(filename.c_str(), ios::binary);

	for (int i = 0; i < 256; i++) {
		fs.read((char*)&mColours[i], sizeof(int));
	}

	fs.close();
}

PaletteFile::~PaletteFile()
{
}