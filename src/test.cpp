#include "Black.h"

#include <cmath>
#include <iostream>
#include <vector>

#include "OpenDM.h"

using namespace std;

void preRenderHook(void)
{
    BlackEngine *engine;
    engine->getGraphicsContext()->setPerspectiveView(FIELD_OF_VISION, 1, 0.1, 100);
}

class HUDObject : public GameObject
{
public:
    HUDObject(string name) : GameObject(name)
    {
        setPerspectiveType("hud");
    }

    virtual bool receive(const Message& message)
    {
    }

    virtual void update(GameObject *obj, unsigned int tick)
    {
    }

    virtual void render(GraphicsContext &context, float interpolation)
    {
        glLoadName(1);
        glBegin(GL_QUADS);
          glColor3f(1.0, 0, 0);
          glVertex3f(0, 0, 0);
          glVertex3f(0, 0.1, 0);
          glVertex3f(0.1, 0.1, 0);
          glVertex3f(0.1, 0, 0);
        glEnd();
    }
};

int main(int argc, char *argv[])
{
    BlackEngine *engine = BlackEngine::get();

    engine->initGraphicsContext(1280, 1024, false);
    engine->switchGameState("play-state");
    engine->getGraphicsContext()->setViewport(0, 0, 1280, 1024);
    engine->setKeyRepeat(500, 50);
    engine->setFieldOfVision(FIELD_OF_VISION);

    StepCamera camera("step-camera", 0, 0, 0);
    engine->setCamera(&camera);

    glDisable(GL_LIGHTING);

    glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0,0,0, 0, 2, 50, 0, 1.0, 0);

    FileImageTexture wallTexture("media/wall1.jpg");
    FileImageTexture floorTexture("media/floor.jpg");

    DataReader dr("data/map1.map");
    dr.buildMap(&wallTexture, &floorTexture);
    dr.setCamera(camera);

    StateManager stateManager(&dr);
    camera.setStateManager(&stateManager);

    engine->getActiveGameState()->registerBroadcastReceiver("sdl-event", &camera);

    HUDObject *hud = new HUDObject("hud");

    engine->mainloop();

    return 0;
}
