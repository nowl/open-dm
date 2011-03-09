#include "Black.h"

#include <cmath>
#include <iostream>
#include <vector>

#include "SlabRenderer.h"
#include "StepCamera.h"

using namespace std;

class FooObject : public GameObject
{
public:
    FooObject(string name) : GameObject(name) {}

    virtual bool receive(const Message& message)
    {
    }

    virtual void update(GameObject *obj, unsigned int tick)
    {    
    }
};

int main(int argc, char *argv[])
{
    BlackEngine *engine = BlackEngine::get();

    engine->initGraphicsContext(1280, 1024, false);
    engine->switchGameState("play-state");
    engine->getGraphicsContext()->setViewport(0, 0, 1280, 1024);
    engine->setKeyRepeat(500, 50);

    engine->getGraphicsContext()->setPerspectiveView(60, 1, 0.1, 100);

    StepCamera camera("step-camera", 0, 0, -1);
    engine->setCamera(&camera);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0,0,-1, 0, 2, 50, 0, 1.0, 0);

//    SlabRenderer renderer(-0.45, -0.55, -0.5, false, 1);
    SlabRenderer renderer(-0.5, -0.5, -0.5, false, 1);
    FooObject foo1("foo1");
    foo1.setRenderer(&renderer);

//    SlabRenderer rend2(0.45, -0.55, -0.5, false, 1);
    SlabRenderer rend2(0.5, -0.5, -0.5, false, 1);
    FooObject foo2("foo2");
    foo2.setRenderer(&rend2);

    SlabRenderer rend3(-0.5, -0.5, -1.5, true, 1);
    FooObject foo3("foo3");
    foo3.setRenderer(&rend3);

    engine->getActiveGameState()->registerBroadcastReceiver("sdl-event", &camera);

    engine->mainloop();

    return 0;
}
