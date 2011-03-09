#ifndef __SLABRENDERER_H__
#define __SLABRENDERER_H__

#include "Black.h"

class SlabRenderer : public IRenderable
{
public:
    SlabRenderer(float x, float y, float z, bool facing_player, float size);
    
    virtual void Render(GraphicsContext &context, float interpolation, void *data);
    
    float x, y, z, size;
    FileImageTexture texture;
    bool facing_player;
};

#endif // __SLABRENDERER_H__
