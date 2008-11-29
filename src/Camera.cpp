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

