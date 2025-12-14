#include <libdragon.h>
#include <t3d/t3d.h>
#include <t3d/t3dmodel.h>

#define FB_COUNT 3

// From tiny3d examples
float get_time_s()  { return (float)((double)get_ticks_ms() / 1000.0); }
float get_time_ms() { return (float)((double)get_ticks_us() / 1000.0); }

[[noreturn]]
int main()
{
	debug_init_isviewer();
	debug_init_usblog();
	asset_init_compression(2);

  dfs_init(DFS_DEFAULT_LOCATION);

  display_init(RESOLUTION_320x240, DEPTH_16_BPP, FB_COUNT, GAMMA_NONE, FILTERS_RESAMPLE_ANTIALIAS);

  rdpq_init();
  joypad_init();

  t3d_init((T3DInitParams){});
  T3DViewport viewport = t3d_viewport_create_buffered(FB_COUNT);
  rdpq_text_register_font(FONT_BUILTIN_DEBUG_MONO, rdpq_font_load_builtin(FONT_BUILTIN_DEBUG_MONO));


  const T3DVec3 camPos = {{100.0f,25.0f,0}};
  const T3DVec3 camTarget = {{0,0,0}};

  //uint8_t colorAmbient[4] = {80, 50, 50, 0xFF};
  //T3DVec3 lightDirVec = {{1.0f, 1.0f, 0.0f}};
  //uint8_t lightDirColor[4] = {120, 120, 120, 0xFF};
  //t3d_vec3_norm(&lightDirVec);

  for(;;)
  {
    // ======== Update ======== //
    joypad_poll();
    joypad_inputs_t joypad = joypad_get_inputs(JOYPAD_PORT_1);

    t3d_viewport_set_projection(&viewport, T3D_DEG_TO_RAD(65.0f), 10.0f, 100.0f);
    t3d_viewport_look_at(&viewport, &camPos, &camTarget, &(T3DVec3){{0,1,0}});

    // ======== Draw (3D) ======== //
    rdpq_attach(display_get(), display_get_zbuf());
    t3d_frame_start();
    t3d_viewport_attach(&viewport);

    rdpq_set_prim_color(RGBA32(0, 0, 0, 0xFF));

    t3d_screen_clear_color(RGBA32(100, 120, 160, 0xFF));
    t3d_screen_clear_depth();

    //t3d_light_set_ambient(colorAmbient);
    //t3d_light_set_directional(0, lightDirColor, &lightDirVec);
    //t3d_light_set_count(1);

    t3d_matrix_push_pos(1);
    // draw models
    t3d_matrix_pop(1);

    // ======== Draw (2D) ======== //
    rdpq_sync_pipe();

    rdpq_detach_show();
  }
}
