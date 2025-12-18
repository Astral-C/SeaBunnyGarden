#include <libdragon.h>
#include <t3d/t3d.h>
#include <t3d/t3dmodel.h>
#include <entity.h>
#include <camera.h>
#include <gamestate.h>

#define FB_COUNT 3

int main()
{
	debug_init_isviewer();
	debug_init_usblog();
	asset_init_compression(2);

  entity_init(100);

  dfs_init(DFS_DEFAULT_LOCATION);

  display_init(RESOLUTION_320x240, DEPTH_16_BPP, FB_COUNT, GAMMA_NONE, FILTERS_RESAMPLE_ANTIALIAS);

  rdpq_init();
  joypad_init();

  t3d_init((T3DInitParams){});
  T3DViewport viewport = t3d_viewport_create_buffered(FB_COUNT);
  rdpq_text_register_font(FONT_BUILTIN_DEBUG_MONO, rdpq_font_load_builtin(FONT_BUILTIN_DEBUG_MONO));

  uint8_t colorAmbient[4] = {0xAA, 0xAA, 0xAA, 0xFF};

  set_initial_sate(&GameStates.main);

  for(;;)
  {
    // ======== Update ======== //
    joypad_poll();

    t3d_viewport_set_projection(&viewport, T3D_DEG_TO_RAD(65.0f), 10.0f, 600.0f);
    t3d_viewport_look_at(&viewport, get_camera_position(), get_camera_target(), &(T3DVec3){{0,1,0}});

    // ======== Draw (3D) ======== //
    rdpq_attach(display_get(), display_get_zbuf());
    t3d_frame_start();
    t3d_viewport_attach(&viewport);

    rdpq_set_prim_color(RGBA32(0xFF, 0xFF, 0xFF, 0xFF));

    t3d_screen_clear_color(RGBA32(0x28, 0x32, 0x50, 0xFF));
    t3d_screen_clear_depth();

    update_gamestate();
    
    entity_think_all();
    entity_update_all();

    t3d_light_set_ambient(colorAmbient);

    t3d_matrix_push_pos(1);

    // draw models
    entity_draw_all();

    t3d_matrix_pop(1);

    // ======== Draw (2D) ======== //
    camera_debug();

    rdpq_sync_pipe();

    rdpq_detach_show();
  }

  entity_cleanup();
}
