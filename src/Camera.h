#ifndef CAMERA_H
#define CAMERA_H

#include "Object.h"
//Camera class for the 3D environment

class Camera: public Object
{
public:
    Camera();

    ~Camera();

    void moveCameraPos(float x, float y, float z);  //moves the camera position

    void moveCameraView(float x, float y, float z); //moves the camera view point

    void moveCameraUp(float x, float y, float z);   //moves the camera up vector

    //set all the cam stuff in one shot
    void setCam(float positionX, float positionY, float positionZ,
    	        float viewX,     float viewY,     float viewZ,
    	        float upVectorX, float upVectorY, float upVectorZ);
    	        
    //moves pos and view of the camera, adding an offset (easy way to move arround)
    void setOffset(float x, float y, float z);
    
    //cam attributes
    t_vector mPosition;  //position of the camera
    t_vector mView;      //point the cam is looking at
    t_vector mUp;        //up vector to view correctly (0, 1, 0) normally
};

#endif
