#include "Khelljyr/Khelljyr.h"

typedef struct	s_Clock
{
  char		display[10];
  Img		*img;
}		Clock;

static void	graphic_fct(Layer *l, GContext *ctx)
{
  Clock		*ptr = USER_PTR;

  putstr_font(ptr->display, FONT_KEY_GOTHIC_28, 30, 0, ctx);
  draw_image(ptr->img, ctx);
  putstr("Made with\nKhelljyr Pebble Framework !", 0, 138, ctx);
}

static void	clock_timer(struct tm *time, TimeUnits u)
{
  Clock		*clock_ptr = USER_PTR;

  snprintf(clock_ptr->display, sizeof(clock_ptr->display), "%.2d:%.2d:%.2d", time->tm_hour, time->tm_min, time->tm_sec);
  refresh();
}

static void	unload(Window *w)
{
  tick_timer_service_unsubscribe();
}

static void	exec(void *data)
{
  Clock		*clock_ptr = data;

  clock_ptr->img = create_img_pos(RESOURCE_ID_DRAGON, 40, 45);
  create_basic_scene_fullscreen(graphic_fct, NULL, unload);
  tick_timer_service_subscribe(SECOND_UNIT, clock_timer);
}

int		main()
{
  Clock		clock_struct;

  app_init(&clock_struct, exec);
  return (0);
}
