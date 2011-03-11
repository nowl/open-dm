#ifndef __PLANE_RENDERER_H__
#define __PLANE_RENDERER_H__

#include "Black.h"

class PlaneRenderer : public IRenderable
{
public:
    PlaneRenderer(float y, std::string textureFile);
    virtual ~PlaneRenderer();
    
    virtual void Render(GraphicsContext &context, float interpolation, void *data);
    
private:
    int y;
    FileImageTexture texture;
};

#endif  // __PLANE_RENDERER_H__
