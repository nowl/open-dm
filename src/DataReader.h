#ifndef __DATA_READER_H__
#define __DATA_READER_H__

#include "Black.h"

#include "StepCamera.h"

class DataReader
{
public:
    DataReader(const std::string& filename);
    ~DataReader();

    void buildMap(const Texture& texture);
    void setCamera(StepCamera& cam);

private:
    std::string filename;
    void processFile();
    
    struct Map
    {
        Map(unsigned int width, unsigned int height)
            : width(width), height(height), tiles(new char[width*height])
        {}
        
        ~Map()
        {
            delete [] tiles;
        }
        
        unsigned int width, height;
        char *tiles;
        unsigned int start_x, start_y, facing;
    };

    Map *map;
};

#endif  // __DATA_READER_H__
