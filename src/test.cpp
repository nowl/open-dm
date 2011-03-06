#include "Black.h"

#include <iostream>
#include <cmath>
#include <vector>

using namespace std;

#if 0

class HexRenderer : public IRenderable
{
public:
    HexRenderer(float x, float y, float z, float radius)
        : x(x), y(y), z(z), radius(radius)
    {
        r = (float)rand()/RAND_MAX;
        g = (float)rand()/RAND_MAX;
        b = (float)rand()/RAND_MAX;
    }

    virtual void Render(GraphicsContext &context, float interpolation, void *data)
    {
        glLoadIdentity();

        glTranslatef(x, y, z);
        glScalef(radius, radius, 0.0f);

        glBegin( GL_TRIANGLE_FAN );
            //glTexCoord2f( 0, 0 );
            glColor3f(r, g, b);
            glVertex3f( 0.0f, 0.0f, 0.0f );
            glVertex3f( 1.0f, 0.0f, 0.0f );
            glVertex3f( 0.5f, sqrtf(3)/2, 0.0f );
            glVertex3f( -0.5f, sqrtf(3)/2, 0.0f );
            glVertex3f( -1.0f, 0.0f, 0.0f );
            glVertex3f( -0.5f, -sqrtf(3)/2, 0.0f );
            glVertex3f( 0.5f, -sqrtf(3)/2, 0.0f );
            glVertex3f( 1.0f, 0.0f, 0.0f );
        glEnd();
    }

private:
    float x, y, z, radius, r, g, b;
};

class FooRenderer : public IRenderable
{
public:
    FooRenderer()
        : shader("hello-gl.vert", "hello-gl.frag"), loop(0), texture("image.bmp")
    {}

    virtual void Render(GraphicsContext &context, float interpolation, void *data)
    {
        shader.bind();
        texture.bind();

        glTranslatef(1280/2, 1024/2, 0);
        glRotatef(loop * .2, 0, 0, 1);
        //if(loop % 4000 == 0)
            //sign *= -1;
        //if(sign == 1)
            //glScalef(0.999, 0.999, 0.999);
        //else
            //glScalef(1.001, 1.001, 1.001);
        glTranslatef(-1280/2, -1024/2, 0);

        glColor3f(1.0, 1.0, 1.0);
        glBegin( GL_QUADS );
            glTexCoord2f( 0, 0 );
            glVertex3f( 100.f, 100.f, 0.0f );
            glTexCoord2f( 1, 0 );
            glVertex3f( 228.f, 100.f, 0.f );
            glTexCoord2f( 1, 1 );
            glVertex3f( 228.f, 228.f, 0.f );
            glTexCoord2f( 0, 1 );
            glVertex3f( 100.f, 228.f, 0.f );
        glEnd();

        glBegin( GL_QUADS );
            glTexCoord2f( 0, 0 );
            glVertex3f( 300.f, 300.f, 0.0f );
            glTexCoord2f( 1, 0 );
            glVertex3f( 428.f, 300.f, 0.f );
            glTexCoord2f( 1, 1 );
            glVertex3f( 428.f, 428.f, 0.f );
            glTexCoord2f( 0, 1 );
            glVertex3f( 300.f, 428.f, 0.f );
        glEnd();

        shader.unbind();
        texture.unbind();

        loop++;
    }

    int sign;

private:
    Shader shader;
    FileImageTexture texture;
    int loop;
};

class OrthoCameraController
{
public:
    OrthoCameraController(int width, int height, int screenWidth, int screenHeight)
        : rect(0, 1280, 0, 1024), dx(0), dy(0), speed(0.99), initSpeed(5),
          destW(0), destH(0), dw(0), dh(0),
          screenWidth(screenWidth), screenHeight(screenHeight)
    {
        glViewport( 0, 0, width, height );
        _setOrtho();
    }

    void centerAt(int screenX, int screenY)
    {
        float x_factor = (float)screenX/screenWidth;
        float y_factor = (float)screenY/screenHeight;

        destX = rect.width * x_factor + rect.left;
        destY = rect.height * y_factor + rect.bottom;

        dx = destX > rect.x ? initSpeed : -initSpeed;
        dy = destY > rect.y ? initSpeed : -initSpeed;
    }

    void zoom(float level)
    {
        destH = rect.height*level;
        destW = rect.width*level;

        rect.setHeight(destH);
        rect.setWidth(destW);
    }

    void update()
    {
        bool needs_update = false;

        if(abs(dx) > 0)
        {
            rect.moveX(dx);
            if(abs(rect.x-destX) <= initSpeed)
            {
                rect.setX(destX);
                dx = 0;
            }

            needs_update = true;
        }

        if(abs(dy) > 0)
        {
            rect.moveY(dy);
            dy *= speed;
            if(abs(rect.y-destY) <= initSpeed)
            {
                rect.setY(destY);
                dy = 0;
            }

            needs_update = true;
        }

        if(needs_update)
        {
            _setOrtho();
        }
    }

private:
    void _setOrtho()
    {
        glMatrixMode( GL_PROJECTION );
        glLoadIdentity();
        glOrtho(rect.left, rect.right, rect.top, rect.bottom, -1.0f, 1.0f);
    }

    Rect rect;
    float destX, destY, dx, dy, speed, initSpeed;
    float destW, destH, dw, dh;
    int screenWidth, screenHeight;
};

int main(int argc, char *argv[])
{
    srand(time(NULL));

    HashedString hs("testing");

    cout << hs.getString() << ": " << hs.getHash() << endl;

    hs = HashedString("testing2");
    cout << hs.getString() << ": " << hs.getHash() << endl;

    GraphicsContext gc(1280, 1024, false);

    vector<IRenderable*> renderers;
    GameObject foo;
    foo.Renderer = new FooRenderer();

    float rad = 100;
    for(int x=0; x<100; x++) {
        for(int y=0; y<100; y++) {
            if(x % 2 == 0)
                renderers.push_back(new HexRenderer(5 + 3.0/2*rad * x, 5 + sqrtf(3)*rad * y, 0, rad));
            else
                renderers.push_back(new HexRenderer(5 + 3.0/2*rad * x, 5 + (2*y+1) * sqrtf(3)/2*rad, 0, rad));

        }
    }

    glClearColor( 0.0f, 0.0f, 0.0f, 0.0f );
    glClear( GL_COLOR_BUFFER_BIT );

    OrthoCameraController camera(1280, 1024, 1280, 1024);

    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();

    float w = 1280;
    float h = 1024;

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // message processing loop
    SDL_Event event;
    bool done = false;
    //foo.sign = -1;
    int loop = 0;
    while(!done) {
        while(SDL_PollEvent(&event))
        {
            if(event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE)
                done = true;
            if(event.type == SDL_MOUSEBUTTONDOWN)
            {
                if(event.button.button == SDL_BUTTON_WHEELDOWN)
                {
                    camera.zoom(1.05);
                }
                else if(event.button.button == SDL_BUTTON_WHEELUP)
                {
                    camera.zoom(0.95);
                } else
                    camera.centerAt(event.button.x, event.button.y);
            }
                //foo.sign *= -1;
        }

        camera.update();
        glMatrixMode( GL_MODELVIEW );

        glClear(GL_COLOR_BUFFER_BIT);

        vector<IRenderable*>::iterator iter = renderers.begin();
        while(iter != renderers.end())
        {
            (*iter)->Render(gc, 0, NULL);
            iter++;
        }

        foo.Renderer->Render(gc, 0, &foo);

        SDL_GL_SwapBuffers();

        loop++;
    }

    return 0;
}

#endif

class HexRenderer : public IRenderable
{
public:
    HexRenderer(float x, float y, float z, float radius)
        : x(x), y(y), z(z), radius(radius)
    {
        r = (float)rand()/RAND_MAX;
        g = (float)rand()/RAND_MAX;
        b = (float)rand()/RAND_MAX;
    }

    virtual void Render(GraphicsContext &context, float interpolation, void *data)
    {
        glLoadIdentity();
        glTranslatef(x, y, z);
        glScalef(radius, radius, 0.0f);

        glBegin( GL_TRIANGLE_FAN );
            //glTexCoord2f( 0, 0 );
            glColor3f(r, g, b);
            glVertex3f( 0.0f, 0.0f, 0.0f );
            glVertex3f( 1.0f, 0.0f, 0.0f );
            glVertex3f( 0.5f, sqrtf(3)/2, 0.0f );
            glVertex3f( -0.5f, sqrtf(3)/2, 0.0f );
            glVertex3f( -1.0f, 0.0f, 0.0f );
            glVertex3f( -0.5f, -sqrtf(3)/2, 0.0f );
            glVertex3f( 0.5f, -sqrtf(3)/2, 0.0f );
            glVertex3f( 1.0f, 0.0f, 0.0f );
        glEnd();
    }

    float x, y, z, radius, r, g, b;
};

class FooObject : public GameObject
{
public:
    FooObject() : dx(0), dy(0), dz(0) {}

    virtual bool receive(const Message& message)
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
                    case SDLK_RIGHT:
                        setVelocity(10, 0, 0);
                        return true;
                    case SDLK_UP:
                        setVelocity(0, -10, 0);
                        return true;
                    case SDLK_DOWN:
                        setVelocity(0, 10, 0);
                        return true;
                    case SDLK_LEFT:
                        setVelocity(-10, 0, 0);
                        return true;
                }
            }
        }

        return false;
    }

    virtual void update(GameObject *obj, unsigned int tick)
    {
        HexRenderer *r = dynamic_cast<HexRenderer*>(Renderer);
        r->x += dx;
        r->y += dy;
        r->z += dz;
        dx *= .95;
        dy *= .95;
        dz *= .95;
        if(abs(dx) < 0.1) dx = 0;
        if(abs(dy) < 0.1) dy = 0;
        if(abs(dz) < 0.1) dz = 0;
    }

private:

    void setVelocity(float x, float y, float z)
    {
        dx = x;
        dy = y;
        dz = z;
    }

    float dx, dy, dz;
};

int main(int argc, char *argv[])
{
    BlackEngine *engine = BlackEngine::get();

    engine->initGraphicsContext(1280, 1024, false);
    engine->getGraphicsContext()->setOrthoView(Rect(0, 1280, 0, 1024));
    engine->getGraphicsContext()->setViewport(0, 0, 1280, 1024);
    engine->setKeyRepeat(500, 50);

    HexRenderer renderer(200, 200, 0, 40);
    FooObject foo;
    foo.setRenderer(&renderer);

    engine->getObjectManager()->registerBroadcastReceiver("sdl-event", &foo);

    engine->mainloop();

    return 0;
}
