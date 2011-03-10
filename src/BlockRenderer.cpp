#include "BlockRenderer.h"

BlockRenderer::BlockRenderer(float x, float y, std::string textureFile)
{
    slab[0] = new SlabRenderer(x-0.5, -0.5, y+0.5, true, 1, textureFile.c_str());
    slab[1] = new SlabRenderer(x-0.5, -0.5, y-0.5, true, 1, textureFile.c_str());
    slab[2] = new SlabRenderer(x-0.5, -0.5, y+0.5, false, 1, textureFile.c_str());
    slab[3] = new SlabRenderer(x+0.5, -0.5, y+0.5, false, 1, textureFile.c_str());
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
        glPushMatrix();
        slab[i]->Render(context, interpolation, data);
        glPopMatrix();
    }
}
