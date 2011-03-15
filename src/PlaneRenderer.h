#ifndef __PLANE_RENDERER_H__
#define __PLANE_RENDERER_H__

#include "Black.h"

class PlaneRenderer : public IRenderable
{
public:
    PlaneRenderer(float y, const Texture& texture);
    virtual ~PlaneRenderer();
    
    virtual void Render(GraphicsContext &context, float interpolation, void *data);
    
private:
    int y;
    const Texture& texture;
};

#endif  // __PLANE_RENDERER_H__
