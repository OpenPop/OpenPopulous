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

//global structs definitions

//vector type for 3d coords (rename someday)
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
	int			mOwnership;

public:
	Object();
	virtual ~Object();

	virtual void Draw();
	virtual void Update();
};

#endif
