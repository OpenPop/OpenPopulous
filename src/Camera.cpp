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

#include "Camera.h"

Camera::Camera()
{
    
}

Camera::~Camera()
{
}

void Camera::moveCameraPos(float x, float y, float z)
{
}

void Camera::moveCameraView(float x, float y, float z)
{
}

void Camera::moveCameraUp(float x, float y, float z)
{
}

//camera stuff - put it on a class!

//sets the contents of a vector
t_vector setVector(float x, float y, float z){
    t_vector temp;
    temp.x = x;
    temp.y = y;
    temp.z = z;
    return temp;
}

//add an offset to a vector and return the result
void setVectorOffset(t_vector &v, float x, float y, float z){
    v.x += x;
    v.y += y;
    v.z += z;
}

void Camera::setCam(float positionX, float positionY, float positionZ,
		            float viewX,     float viewY,     float viewZ,
		            float upVectorX, float upVectorY, float upVectorZ)
{
	t_vector position = setVector(positionX, positionY, positionZ);
	t_vector view	  = setVector(viewX, viewY, viewZ);
	t_vector up       = setVector(upVectorX, upVectorY, upVectorZ);

	// The code above just makes it cleaner to set the variables.
	// Otherwise we would have to set each variable x y and z.

	mPosition = position;					// Assign the position
	mView     = view;						// Assign the view
	mUp       = up;					// Assign the up vector
}

//moves pos and view of the camera, adding an offset (easy way to move arround)
void Camera::setOffset(float x, float y, float z){
    setVectorOffset(mPosition, x, y, z);
    setVectorOffset(mView, x, y, z);
    //up vector is the same usually
}

