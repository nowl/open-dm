#include "open-dm.h"

static void
update(engine_t *engine, game_object_t *obj, unsigned int ticks)
{
    camera_t *c = obj->data;
        
    if(abs(c->dest_x-c->x) <= c->speed)
        c->x = c->dest_x;
    if(c->dest_x != c->x)
    {
        if(c->dest_x > c->x)
            c->x += c->speed;
        else
            c->x -= c->speed;
    }

    if(abs(c->dest_z-c->z) <= c->speed)
        c->z = c->dest_z;
    if(c->dest_z != c->z)
    {
        if(c->dest_z > c->z)
            c->z += c->speed;
        else
            c->z -= c->speed;
    }

    if(c->facing != c->dest_facing)
    {
        if(c->angle >= 360)
            c->angle -= 360;
        if(c->angle < 0)
            c->angle += 360;

        float dest_angle;

        switch((c->dest_facing << 0x2) | c->facing)
        {
        case 0x1:
            // WEST going on NORTH
            dest_angle = 0;
            c->angle += c->turn_speed;
            break;
        case 0x3:
            // EAST going on NORTH
            dest_angle = 0;
            c->angle -= c->turn_speed;
            break;
        case 0x4:
            // NORTH going on WEST
            dest_angle = 270;
            c->angle -= c->turn_speed;
            break;
        case 0x6:
            // SOUTH going on WEST
            dest_angle = 270;
            c->angle += c->turn_speed;
            break;
        case 0x9:
            // WEST going on SOUTH
            dest_angle = 180;
            c->angle -= c->turn_speed;
            break;
        case 0xb:
            // EAST going on SOUTH
            dest_angle = 180;
            c->angle += c->turn_speed;
            break;
        case 0xc:
            // NORTH going on EAST
            dest_angle = 90;
            c->angle += c->turn_speed;
            break;
        case 0xe:
            // SOUTH going on EAST
            dest_angle = 90;
            c->angle -= c->turn_speed;
            break;
        }

        if(abs(dest_angle - c->angle) <= c->turn_speed)
        {
            c->facing = c->dest_facing;
            c->angle = dest_angle;
        }
    }

    /*
    LOG("angle: %f, facing: %d, dest-facing: %d\n", 
        c->angle, c->facing, c->dest_facing);
    */
}

static void attempt_move(camera_t *camera, int dx, int dy)
{
    camera->dest_x += dx;
    camera->dest_z += dy;
}

static int mhandler(game_object_t *obj, message_t *mes)
{
    camera_t *c = obj->data;

    if(mes->type == lapis_hash("sdl-event"))
    {
        SDL_Event *event = mes->data->data;
        if(event->type == SDL_KEYDOWN)
        {
            switch(event->key.keysym.sym)
            {
            case SDLK_e:
                switch(c->facing)
                {
                case NORTH:
                    c->dest_facing = EAST;
                    break;
                case EAST:
                    c->dest_facing = SOUTH;
                    break;
                case SOUTH:
                    c->dest_facing = WEST;
                    break;
                case WEST:
                    c->dest_facing = NORTH;
                    break;
                }
                return 1;
            case SDLK_w:
                switch(c->facing)
                {
                case NORTH:
                    attempt_move(c, 0, 1);
                    break;
                case WEST:
                    attempt_move(c, 1, 0);
                    break;
                case SOUTH:
                    attempt_move(c, 0, -1);
                    break;
                case EAST:
                    attempt_move(c, -1, 0);
                    break;
                }
                return 1;
            case SDLK_s:
                switch(c->facing)
                {
                case NORTH:
                    attempt_move(c, 0, -1);
                    break;
                case WEST:
                    attempt_move(c, -1, 0);
                    break;
                case SOUTH:
                    attempt_move(c, 0, 1);
                    break;
                case EAST:
                    attempt_move(c, 1, 0);
                    break;
                }
                return 1;
            case SDLK_q:
                switch(c->facing)
                {
                case NORTH:
                    c->dest_facing = WEST;
                    break;
                case WEST:
                    c->dest_facing = SOUTH;
                    break;
                case SOUTH:
                    c->dest_facing = EAST;
                    break;
                case EAST:
                    c->dest_facing = NORTH;
                    break;
                }
                return 1;
            case SDLK_a:
                switch(c->facing)
                {
                case NORTH:
                    attempt_move(c, 1, 0);
                    break;
                case WEST:
                    attempt_move(c, 0, -1);
                    break;
                case SOUTH:
                    attempt_move(c, -1, 0);
                    break;
                case EAST:
                    attempt_move(c, 0, 1);
                    break;
                }
                return 1;
            case SDLK_d:
                switch(c->facing)
                {
                case NORTH:
                    attempt_move(c, -1, 0);
                    break;
                case WEST:
                    attempt_move(c, 0, 1);
                    break;
                case SOUTH:
                    attempt_move(c, 1, 0);
                    break;
                case EAST:
                    attempt_move(c, 0, -1);
                    break;
                }
                return 1;
            default:
                return 0;
            }
        }
    }

    return 0;
}

static void camera_set_view(enum render_wrap wrap_type, camera_t *cam)
{
    if(wrap_type == RW_PRE)
    {
        glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
                
        glPushMatrix();
        
        //glLoadIdentity();
       
        // adjust for facing
        glRotatef(cam->angle, 0, 1, 0);

        glTranslatef(cam->x, cam->y, cam->z);
    }
    else if(wrap_type == RW_POST)
    {
        glPopMatrix();
    }
}

camera_t *camera_create(float x, float y, float z)
{
    camera_t *camera = malloc(sizeof(*camera));
    camera->x = x;
    camera->y = y;
    camera->z = z;
    camera->dest_x = x;
    camera->dest_y = y;
    camera->dest_z = z;
    camera->speed = 0.1;
    camera->facing = camera->dest_facing = NORTH;
    camera->angle = 0;
    camera->turn_speed = 90/10*2;

    game_object_t *go = game_object_create("camera", camera);
    camera->go = go;
    game_state_append_object(lapis_get_engine()->state, go);
    game_object_set_update_callback_c_func(go, update);
    game_object_set_recv_callback_c_func(go, mhandler);
    game_state_append_bcast_recvr(lapis_get_engine()->state, go, "sdl-event");

    engine_set_render_wrap_hook(lapis_get_engine(), camera_set_view, camera);
   
    return camera;
}

void camera_destroy(camera_t *camera)
{
    free(camera);
}
