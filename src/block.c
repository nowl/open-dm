#include "open-dm.h"

static int block_count = 0;

static void
render(engine_t *engine, game_object_t *obj, float interpolation)
{
    block_t *b = obj->data;
    int i;

    for(i=0; i<4; i++)
    {
        glPushMatrix();

        float x = b->slab[i].x;
        float y = b->slab[i].y;
        float z = b->slab[i].z;
    
        glTranslatef(x, y, z);
        //glScalef(size, size, size);

        switch(b->slab[i].slab_type)
        {
        case ST_SIDE:
            glRotatef(90, 0, 1, 0);
            break;
        case ST_PARALLEL:
            glRotatef(90, 1, 0, 0);
            break;
        }

        glBegin(GL_QUADS);
        //glColor3f(val, val, val);
        glColor3f(1, 1, 1);
        //glTexCoord2f(0, 0);
        glVertex3f(0, 0, 0);
        //glTexCoord2f(0, 1);
        glVertex3f(0, 1, 0);
        //glTexCoord2f(1, 1);
        glVertex3f(1, 1, 0);
        //glTexCoord2f(1, 0);
        glVertex3f(1, 0, 0);
        glEnd();
        
        glPopMatrix();
    }
}

block_t *block_create(float x, float y)
{
    block_t *block = malloc(sizeof(*block));
    char *block_name;
    asprintf(&block_name, "block %d", block_count++);
    block->go = game_object_create(block_name, block);
    block->go->render_level = RL_BLOCKS;
    game_state_append_object(lapis_get_engine()->state,
                             block->go);
    game_object_set_render_callback_c_func(block->go, render);
    free(block_name);

    /* fill in slabs */
    block->slab[0].x = -x-0.5;
    block->slab[0].y = -0.5;
    block->slab[0].z = -y+0.5;
    block->slab[0].slab_type = ST_FRONT;
    block->slab[1].x = -x-0.5;
    block->slab[1].y = -0.5;
    block->slab[1].z = -y-0.5;
    block->slab[1].slab_type = ST_FRONT;
    block->slab[2].x = -x-0.5;
    block->slab[2].y = -0.5;
    block->slab[2].z = -y+0.5;
    block->slab[2].slab_type = ST_SIDE;
    block->slab[3].x = -x+0.5;
    block->slab[3].y = -0.5;
    block->slab[3].z = -y+0.5;
    block->slab[3].slab_type = ST_SIDE;

    return block;
}

void block_destroy(block_t *block)
{
    free(block);
}
