#ifndef __BLOCK_RENDERER_H__
#define __BLOCK_RENDERER_H__

#include "Black.h"
#include "SlabRenderer.h"

class BlockRenderer : public IRenderable
{
public:
    BlockRenderer(float x, float y, Texture* texture);
    virtual ~BlockRenderer();
    
    virtual void Render(GraphicsContext &context, float interpolation, void *data);
    
private:
    SlabRenderer *slab[4];
};


#endif  // __BLOCK_RENDERER_H__
