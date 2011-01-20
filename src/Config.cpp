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

#include "stdafx.h"

#include <windows.h>
#include <Shlobj.h>
#include "Config.h"

using namespace std;

Config* gConfig = new Config();

BOOL Is64BitOperatingSystem();

Config::Config()
{
	TCHAR szProgramFiles[MAX_PATH];
	SHGetSpecialFolderPath(NULL, szProgramFiles, CSIDL_PROGRAM_FILES, FALSE);
	strcat(szProgramFiles, "\\Bullfrog\\Populous\\");

	mPopDirectory = szProgramFiles;
}

Config::~Config()
{

}

string Config::GetPopFile(string path)
{
	return mPopDirectory + path;
}