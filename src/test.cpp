#include "Black.h"

#include <cmath>
#include <iostream>
#include <vector>

#include "BlockRenderer.h"
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

    engine->getGraphicsContext()->setPerspectiveView(120, 1, 0.1, 100);

    StepCamera camera("step-camera", 0, 0, 0);
    engine->setCamera(&camera);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0,0,0, 0, 2, 50, 0, 1.0, 0);

    BlockRenderer blockRenderer1(0, 0, "media/wall1.tif");
    //BlockRenderer blockRenderer2(1, 0, "media/wall1.tif");
    //BlockRenderer blockRenderer3(2, 0, "media/wall1.tif");
    //BlockRenderer blockRenderer4(3, 0, "media/wall1.tif");

    FooObject foo1("foo1"); foo1.setRenderer(&blockRenderer1);
    //FooObject foo2("foo2"); foo1.setRenderer(&blockRenderer2);
    //FooObject foo3("foo3"); foo1.setRenderer(&blockRenderer3);
    //FooObject foo4("foo4"); foo1.setRenderer(&blockRenderer4);

    engine->getActiveGameState()->registerBroadcastReceiver("sdl-event", &camera);

    engine->mainloop();

    return 0;
}
