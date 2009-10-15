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

#ifndef _OBJECT_H_
#define _OBJECT_H_

#include <vector>

//global structs definitions

typedef struct{
    float x;
    float y;
    float z;
}t_vector;

//Object class, root of the class tree

class Object
{
public:
	float		mAngle;
	float		mX, mY, mZ;
	int			mTribe;

public:
	Object();
	virtual ~Object();

	virtual void Draw();
	virtual void Update();
};

typedef std::vector<Object*> ObjectList;

#endif
