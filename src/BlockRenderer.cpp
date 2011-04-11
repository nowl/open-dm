#include "BlockRenderer.h"

BlockRenderer::BlockRenderer(float x, float y,
                             Texture* texture)
{
    slab[0] = new SlabRenderer(-x-0.5, -0.5, -y+0.5, SlabRenderer::FRONT, 1, texture);
    slab[1] = new SlabRenderer(-x-0.5, -0.5, -y-0.5, SlabRenderer::FRONT, 1, texture);
    slab[2] = new SlabRenderer(-x-0.5, -0.5, -y+0.5, SlabRenderer::SIDE, 1, texture);
    slab[3] = new SlabRenderer(-x+0.5, -0.5, -y+0.5, SlabRenderer::SIDE, 1, texture);
}

BlockRenderer::~BlockRenderer()
{
    for(int i=0; i<4; i++)
        delete slab[i];
}

void
BlockRenderer::Render(GraphicsContext &context, float interpolation, void *data)
{
    for(int i=0; i<4; i++)
    {
        glLoadName(7);
        glPushMatrix();
        slab[i]->Render(context, interpolation, data);
        glPopMatrix();
    }
}
