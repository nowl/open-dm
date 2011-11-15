#include "open-dm.h"

#define WIDTH 1024
#define HEIGHT 768

#define FIELD_OF_VISION 100

int global_message_handler(game_object_t *obj, message_t *mes)
{
    if(mes->type == lapis_hash("sdl-event"))
    {
        SDL_Event *event = mes->data->data;
        if(event->type == SDL_KEYDOWN)
        {
            switch(event->key.keysym.sym)
            {
            case SDLK_ESCAPE:
                engine_quit(lapis_get_engine());
                return 1;
            default:
                break;
            }
        }
        else if(event->type == SDL_QUIT)
        {
            engine_quit(lapis_get_engine());
            return 1;
        }
        else if(event->type == SDL_VIDEORESIZE)
        {

        }
    }

    return 0;
}                    

int main(int argc, char *argv[])
{
    lapis_init();
    
    engine_t *engine = lapis_get_engine();
    set_ticks_per_second(30);

    game_state_t *state = game_state_create(0);
    state->num_render_levels = RL_NUM;

    engine_switch_state(engine, state);

    /* initialize video */
    
    lsdl_set_video_mode(engine->sdl_driver,
                        WIDTH, HEIGHT, 0, 1);

    SDL_EnableKeyRepeat(500, 50);
    SDL_WM_SetCaption( "Open DM v. 0.1", NULL );

    glMatrixMode( GL_PROJECTION );
    glLoadIdentity( );
    gluPerspective(FIELD_OF_VISION, 1, 0.1, 100);

//    glEnable(GL_TEXTURE_2D);

    glClearColor( 0.0f, 0.0f, 0.0f, 0.0f );
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_DEPTH_TEST);
//    glDisable(GL_LIGHTING);
//    glEnable(GL_LIGHTING);

    glViewport(0, 0, WIDTH, HEIGHT);

    glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0,0,0, 0, 0, -10, 0, 1.0, 0);
    
    /* test */
    /* load graphics */
//    lapis_lua_t *lua = lua_scripting_init();
//    if( lua_scripting_run_file(lua, "main.lua") != 0 )
//        return 0;
    /* end test */

    /* create objects */

    game_object_t * global_object = game_object_create("global", NULL);
    game_state_append_object(state, global_object);
    game_object_set_recv_callback_c_func(global_object, global_message_handler);
    game_state_append_bcast_recvr(state,
                                  global_object,
                                  "sdl-event");

    block_t *block = block_create(1, 1);
    game_state_append_object(state, block->go);

    camera_t *camera = camera_create(0, 0, 0);
    game_state_append_object(state, camera->go);
       
    lapis_mainloop();

    /* this will be cleaned up by the OS */
    //game_state_destroy(state);
    //lapis_deinit();

    return 0;
}
