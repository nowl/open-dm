#ifndef __OPENDM_H__
#define __OPENDM_H__

#include "lapis.h"

enum render_level {
    RL_BLOCKS,

    RL_NUM                      /* number of render levels */
};

enum slab_type_e {
    ST_FRONT,
    ST_SIDE,
    ST_PARALLEL
};

typedef struct block block_t;
struct block {
    game_object_t *go;
    int x, y;
    
    struct {
        float x, y, z;
        enum slab_type_e slab_type;
    } slab[4];
};

block_t *block_create(float x, float y);
void     block_destroy(block_t *block);

typedef enum {
    NORTH = 0,
    WEST,
    SOUTH,
    EAST
} facing_t;

typedef struct camera camera_t;
struct camera {
    game_object_t *go;
    float x, y, z;
    float dest_x, dest_y, dest_z;
    float speed;
  
    facing_t facing, dest_facing;

    float angle, turn_speed;
};

camera_t *camera_create(float x, float y, float z);
void      camera_destroy(camera_t *camera);

#endif  /* __OPENDM_H__ */
