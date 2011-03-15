#include "Black.h"

#include <cmath>
#include <iostream>
#include <vector>

#include "StepCamera.h"
#include "DataReader.h"

using namespace std;

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

    FileImageTexture texture("media/wall1.jpg");

    DataReader dr("data/map1.map");
    dr.buildMap(texture);
    dr.setCamera(camera);

    engine->getActiveGameState()->registerBroadcastReceiver("sdl-event", &camera);

    engine->mainloop();

    return 0;
}
