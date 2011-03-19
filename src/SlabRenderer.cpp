#include <cmath>

#include "SlabRenderer.h"

SlabRenderer::SlabRenderer(float x, float y, float z, SlabType slabType, float size, 
                           Texture* texture)
    : x(x), y(y), z(z), size(size),
      texture(texture), slabType(slabType)
{}

static float mDistance(float x1, float y1, float x2, float y2)
{
    return fabs(x1-x2) + fabs(y1-y2);
}

void
SlabRenderer::Render(GraphicsContext &context, float interpolation, void *data)
{
    if(texture)
        texture->bind();

    glTranslatef(x, y, z);
    glScalef(size, size, size);

    switch(slabType)
    {
    case SIDE:
        glRotatef(90, 0, 1, 0);
        break;
    case PARALLEL:
        glRotatef(90, 1, 0, 0);
        break;
    }

    Camera *camera = BlackEngine::get()->getCamera();
    Camera::Point p = camera->getPosition();

    float dist = mDistance(-x, -z, p.x, p.z);
    float val = -1/5.0 * dist + 1;
    if(val < 0)
        val = 0;
    
    glBegin(GL_QUADS);
      glColor3f(val, val, val);
      glTexCoord2f(0, 0);
      glVertex3f(0, 0, 0);
      glTexCoord2f(0, 1);
      glVertex3f(0, 1, 0);
      glTexCoord2f(1, 1);
      glVertex3f(1, 1, 0);
      glTexCoord2f(1, 0);
      glVertex3f(1, 0, 0);
    glEnd();
    
    if(texture)
        texture->unbind();
}
