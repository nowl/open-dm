#include <sstream>
#include <stdexcept>

#include "Black.h"

#include "DataReader.h"
#include "UniqueName.h"
#include "File.h"
#include "BlockRenderer.h"
#include "PlaneRenderer.h"

using namespace std;

DataReader::DataReader(const string& filename)
    : filename(filename), map(NULL)
{
    processFile();
}

DataReader::~DataReader()
{
    if(map)
        delete map;
}

// Note: This should only be called from the constructor.
void
DataReader::processFile()
{
    // TODO: fix lineNum
    int lineNum = 1;

    File f(filename.c_str(), "r");
    FILE *FIN = f.getFP();

    printf("reading map: %s\n", filename.c_str());

    int width, height;
    int result = fscanf(FIN, "%u,%u", &width, &height);

    if(result != 2)
    {
        stringstream str;
        str << "problem parsing " << filename << " near line " << lineNum;
        throw runtime_error(str.str());
    }
    
    map = new Map(width, height);

    for(int i=0; i<width*height; i++)
    {
        result = fscanf(FIN, "%u%*[, ]", &map->tiles[i]);
        if(result != 1)
        {
            stringstream str;
            str << "problem parsing " << filename << " near line " << lineNum;
                throw runtime_error(str.str());
        }
    }
}

class FooObject : public GameObject
{
public:
    FooObject(string name) : GameObject(name) {}

    virtual bool receive(const Message& message)
    {
    }

    virtual void update(GameObject *obj, unsigned int tick)
    {    
    }
};

void
DataReader::buildMap(const Texture& texture)
{    
    for(int x=0; x<map->width; x++)
        for(int y=0; y<map->height; y++)
        {
            if(map->tiles[y * map->width + x] == 0)
            {
                BlockRenderer *blockRenderer = new BlockRenderer(x, y, texture);
                FooObject *foo = new FooObject(UniqueName("slab").getName());
                foo->setRenderer(blockRenderer);
            }
        }

    PlaneRenderer *ceilingRenderer = new PlaneRenderer(1, texture);
    FooObject *ceiling = new FooObject("ceiling");
    ceiling->setRenderer(ceilingRenderer);
    PlaneRenderer *floorRenderer = new PlaneRenderer(-1, texture);
    FooObject *floor = new FooObject("floor");
    floor->setRenderer(floorRenderer);
}
