#ifndef __SLABRENDERER_H__
#define __SLABRENDERER_H__

#include "Black.h"

class SlabRenderer : public IRenderable
{
public:

    enum SlabType
    {
        FRONT,
        SIDE,
        PARALLEL
    };

    SlabRenderer(float x, float y, float z, SlabType slabType, float size, 
                 Texture* texture);
    
    virtual void Render(GraphicsContext &context, float interpolation, void *data);
    
    float x, y, z, size;
    Texture* texture;
    SlabType slabType;
};

#endif // __SLABRENDERER_H__
