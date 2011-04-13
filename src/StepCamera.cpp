#include "OpenDM.h"

// TODO: remove (testing)
#include <vector>
#include <string>
using namespace std;

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
StepCamera::setView(GameObject *obj, ObjectManager::RenderType type)
{
    if(obj->getPerspectiveType() == "world")
    {
        glMatrixMode(GL_MODELVIEW);

        // adjust for facing
        glRotatef(angle, 0, 1, 0);

        glTranslatef(x, y, z);
    }
}

void
StepCamera::setPerspectiveView(GameObject *obj, ObjectManager::RenderType type)
{
    BlackEngine *engine;

    switch(type)
    {
    case ObjectManager::DRAW:
        if(obj->getPerspectiveType() == "world")
            engine->getGraphicsContext()->setPerspectiveView(FIELD_OF_VISION, 1, 0.1, 100);
        else if(obj->getPerspectiveType() == "hud")
            engine->getGraphicsContext()->setOrthoView(Rect(-1, 1, -1, 1));
        break;
    case ObjectManager::PICKING:
        if(obj->getPerspectiveType() == "world")
            gluPerspective(BlackEngine::get()->getFieldOfVision(), 1.0, 0.0001, 1000.0);
        else if(obj->getPerspectiveType() == "hud")
            glOrtho(-1, 1, -1, 1, -1.0f, 1.0f);
        break;
    default:
        printf("unknown render type\n");
        break;
    }
}

Camera::Point
StepCamera::getPosition()
{
    Point p = {x, y, z};
    return p;
}

void
StepCamera::update(GameObject *obj, unsigned int tick)
{
    //printf("position: (%f,%f,%f)\n", x, y, z);

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
            case SDLK_e:
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
            case SDLK_w:
                switch(facing)
                {
                case NORTH:
                    attemptMove(0, 1);
                    break;
                case WEST:
                    attemptMove(1, 0);
                    break;
                case SOUTH:
                    attemptMove(0, -1);
                    break;
                case EAST:
                    attemptMove(-1, 0);
                    break;
                }
                return true;
            case SDLK_s:
                switch(facing)
                {
                case NORTH:
                    attemptMove(0, -1);
                    break;
                case WEST:
                    attemptMove(-1, 0);
                    break;
                case SOUTH:
                    attemptMove(0, 1);
                    break;
                case EAST:
                    attemptMove(1, 0);
                    break;
                }
                return true;
            case SDLK_q:
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
            case SDLK_a:
                switch(facing)
                {
                case NORTH:
                    attemptMove(1, 0);
                    break;
                case WEST:
                    attemptMove(0, -1);
                    break;
                case SOUTH:
                    attemptMove(-1, 0);
                    break;
                case EAST:
                    attemptMove(0, 1);
                    break;
                }
                return true;
            case SDLK_d:
                switch(facing)
                {
                case NORTH:
                    attemptMove(-1, 0);
                    break;
                case WEST:
                    attemptMove(0, 1);
                    break;
                case SOUTH:
                    attemptMove(1, 0);
                    break;
                case EAST:
                    attemptMove(0, -1);
                    break;
                }
                return true;
            }
        }
        else if(event->type == SDL_MOUSEBUTTONDOWN)
        {
            vector<string> picks;
            BlackEngine::get()->getPickManager()->getPicks(event->button.x, event->button.y, picks);
        }
    }

    return false;
}

void
StepCamera::setDest(float x, float z)
{
    dest_x += x;
    dest_z += z;
}

void
StepCamera::attemptMove(int x, int y)
{
    if(StateMan->isEnterable(dest_x + x, dest_z + y))
        setDest(x, y);
}

void
StepCamera::setPosition(float x, float y, unsigned int facing)
{
    this->x = dest_x = x;
    this->z = dest_z = y;
    this->facing = dest_facing = facing;

    switch(facing)
    {
    case NORTH:
        angle = 0;
        break;
    case WEST:
        angle = 270;
        break;
    case SOUTH:
        angle = 180;
        break;
    case EAST:
        angle = 90;
        break;
    }
}

void
StepCamera::setStateManager(StateManager *sm)
{
    StateMan = sm;
}
