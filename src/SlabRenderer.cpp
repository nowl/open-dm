#include "SlabRenderer.h"

SlabRenderer::SlabRenderer(float x, float y, float z, bool facing_player, float size)
    : x(x), y(y), z(z), size(size), facing_player(facing_player),
      texture("media/wall1.tif")
{}

void
SlabRenderer::Render(GraphicsContext &context, float interpolation, void *data)
{
    texture.bind();

    glTranslatef(x, y, z);
    glScalef(size, size, size);

    if(!facing_player)
        glRotatef(90, 0, 1, 0);
    
    glBegin(GL_QUADS);
      glColor3f(1,1,1);
      glTexCoord2f(0, 0);
      glVertex3f(0, 0, 0);
      glTexCoord2f(0, 1);
      glVertex3f(0, 1, 0);
      glTexCoord2f(1, 1);
      glVertex3f(1, 1, 0);
      glTexCoord2f(1, 0);
      glVertex3f(1, 0, 0);
    glEnd();
    
    texture.unbind();
}
