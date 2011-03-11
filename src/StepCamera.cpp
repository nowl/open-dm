#include "StepCamera.h"

StepCamera::StepCamera(std::string name, float x, float y, float z)
    : Camera(name), x(x), y(y), z(z), 
      dest_x(x), dest_y(y), dest_z(z),
      speed(0.1), 
      facing(NORTH), dest_facing(NORTH),
      angle(0), turn_speed(90/10*2)
{}

StepCamera::~StepCamera()
{}

void
StepCamera::setView()
{
    // adjust for facing
    glRotatef(angle, 0, 1, 0);    


    glTranslatef(x, y, z);
}

void
StepCamera::update(GameObject *obj, unsigned int tick)
{
    //printf("(%f,%f,%f)\n", x, y, z);

    if(abs(dest_x-x) <= speed)
        x = dest_x;
    if(dest_x != x)
        if(dest_x > x)
            x += speed;
        else
            x -= speed;

    if(abs(dest_z-z) <= speed)
        z = dest_z;
    if(dest_z != z)
        if(dest_z > z)
            z += speed;
        else
            z -= speed;

    if(facing != dest_facing)
    {
        /*
        if(abs(dest_angle - angle) <= turn_speed)
        {
            facing = dest_facing;
            angle = dest_angle;
        }
        else
        {
            
            switch(dest_angle)
            {
                

            angle += turn_speed * turn_dir;
            if(angle >= 360)
                angle -= 360;
            else if(angle <= -360)
                angle += 360;
        }
        */
        
        if(angle >= 360)
            angle -= 360;
        if(angle < 0)
            angle += 360;

        float dest_angle;

        switch((dest_facing << 0x2) | facing)
        {
        case 0x1:
            // WEST going on NORTH
            dest_angle = 0;
            angle += turn_speed;            
            break;
        case 0x3:
            // EAST going on NORTH
            dest_angle = 0;
            angle -= turn_speed;
            break;
        case 0x4:
            // NORTH going on WEST
            dest_angle = 270;
            angle -= turn_speed;
            break;
        case 0x6:
            // SOUTH going on WEST
            dest_angle = 270;
            angle += turn_speed;
            break;
        case 0x9:
            // WEST going on SOUTH
            dest_angle = 180;
            angle -= turn_speed;
            break;
        case 0xb:
            // EAST going on SOUTH
            dest_angle = 180;
            angle += turn_speed;
            break;
        case 0xc:
            // NORTH going on EAST
            dest_angle = 90;
            angle += turn_speed;
            break;
        case 0xe:
            // SOUTH going on EAST
            dest_angle = 90;
            angle -= turn_speed;
            break;
        }

        if(abs(dest_angle - angle) <= turn_speed)
        {
            facing = dest_facing;
            angle = dest_angle;
        }
    }        
}

bool
StepCamera::receive(const Message& message)
{
    if(message.type == HashedString("sdl-event").getHash())
    {
        SDL_Event *event = (SDL_Event *)message.data;
        if(event->type == SDL_KEYDOWN)
        {
            switch(event->key.keysym.sym)
            {
            case SDLK_ESCAPE:
                BlackEngine::get()->IsRunning = false;
                return true;
            case SDLK_KP6:
                switch(facing)
                {
                case NORTH:
                    dest_facing = EAST;
                    break;
                case EAST:
                    dest_facing = SOUTH;
                    break;
                case SOUTH:
                    dest_facing = WEST;
                    break;
                case WEST:
                    dest_facing = NORTH;
                    break;
                }
                return true;
            case SDLK_KP5:
                switch(facing)
                {
                case NORTH:
                    setDest(0, 1);
                    break;
                case WEST:
                    setDest(1, 0);
                    break;
                case SOUTH:
                    setDest(0, -1);
                    break;
                case EAST:
                    setDest(-1, 0);
                    break;
                }
                return true;
            case SDLK_KP2:
                switch(facing)
                {
                case NORTH:
                    setDest(0, -1);
                    break;
                case WEST:
                    setDest(-1, 0);
                    break;
                case SOUTH:
                    setDest(0, 1);
                    break;
                case EAST:
                    setDest(1, 0);
                    break;
                }
                return true;
            case SDLK_KP4:
                switch(facing)
                {
                case NORTH:
                    dest_facing = WEST;
                    break;
                case WEST:
                    dest_facing = SOUTH;
                    break;
                case SOUTH:
                    dest_facing = EAST;
                    break;
                case EAST:
                    dest_facing = NORTH;
                    break;
                }
                return true;
            case SDLK_KP1:
                switch(facing)
                {
                case NORTH:
                    setDest(1, 0);
                    break;
                case WEST:
                    setDest(0, -1);
                    break;
                case SOUTH:
                    setDest(-1, 0);
                    break;
                case EAST:
                    setDest(0, 1);
                    break;
                }
                return true;
            case SDLK_KP3:
                switch(facing)
                {
                case NORTH:
                    setDest(-1, 0);
                    break;
                case WEST:
                    setDest(0, 1);
                    break;
                case SOUTH:
                    setDest(1, 0);
                    break;
                case EAST:
                    setDest(0, -1);
                    break;
                }
                return true;
            }
        }
    }

    return false;
}

void
StepCamera::setDest(float x, float z)
{
    dest_x = this->x + x;
    dest_z = this->z + z;
}
