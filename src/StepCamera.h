#ifndef __STEP_CAMERA_H__
#define __STEP_CAMERA_H__

#include "Black.h"

class StepCamera : public Camera
{
public:
    
    enum FACING
    {
        NORTH = 0,
        WEST,
        SOUTH,
        EAST
    };
    
    StepCamera(std::string name, float x, float y, float z);
    virtual ~StepCamera();

    virtual void setView();
    virtual Point getPosition();
    virtual void update(GameObject *obj, unsigned int tick);
    virtual bool receive(const Message& message);
    
    void setPosition(float x, float y, unsigned int facing);

private:
    
    void setDest(float x, float z);

    float dest_x, dest_y, dest_z, x, y, z, speed;
    unsigned int facing, dest_facing;
    float angle, turn_speed;
};

#endif  // __STEP_CAMERA_H__
