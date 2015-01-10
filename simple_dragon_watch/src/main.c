#include "Khelljyr/Khelljyr.h"

typedef struct	s_Clock
{
  char		display[10];
  Img		*img;
}		Clock;

static void	graphic_fct(Layer *l, GContext *ctx)
{
  Clock		*ptr = USER_PTR;

  // We display the time with custom font
  putstr_font(ptr->display, FONT_KEY_GOTHIC_28, 30, 0, ctx);

  // We draw the image
  draw_image(ptr->img, ctx);

  // Credits
  putstr("Made with\nKhelljyr Pebble Framework !", 0, 138, ctx);
}

static void	clock_timer(struct tm *time, TimeUnits u)
{
  Clock		*clock_ptr = USER_PTR;

  // We set the display variable
  snprintf(clock_ptr->display, sizeof(clock_ptr->display), "%.2d:%.2d:%.2d", time->tm_hour, time->tm_min, time->tm_sec);

  // The screen has changed, we refresh() it
  refresh();
}

static void	unload(Window *w)
{
  // We unsubscribe on window unloading
  tick_timer_service_unsubscribe();
}

static void	exec(void *data)
{
  Clock		*clock_ptr = data;

  // We create a picture
  clock_ptr->img = create_img_pos(RESOURCE_ID_DRAGON, 40, 45);
  
  // We create a scene in fullscreen
  create_basic_scene_fullscreen(graphic_fct, NULL, unload, NULL);

  // set the time trigger for the time every second
  tick_timer_service_subscribe(SECOND_UNIT, clock_timer);
}

int		main()
{
  // We create our user data
  Clock		clock_struct;

  // We start our loop with user data
  app_init(&clock_struct, exec);
  return (0);
}
