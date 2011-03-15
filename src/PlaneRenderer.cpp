#include "PlaneRenderer.h"

PlaneRenderer::PlaneRenderer(float y, const Texture& texture)
    : y(y), texture(texture)
{}

PlaneRenderer::~PlaneRenderer()
{}

void
PlaneRenderer::Render(GraphicsContext &context, float interpolation, void *data)
{
    texture.bind();

    glTranslatef(0, y, 0);

    glBegin(GL_QUADS);
      //glColor3f(1,1,1);
      glTexCoord2f(0, 0);
      glVertex3f(1000, y, 10000);
      glTexCoord2f(0, 1);
      glVertex3f(1000, y, -1000);
      glTexCoord2f(1, 1);
      glVertex3f(-1000, y, -1000);
      glTexCoord2f(1, 0);
      glVertex3f(-1000, y, 1000);
    glEnd();
    
    texture.unbind();
}
