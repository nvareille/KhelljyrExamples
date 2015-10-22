#include "Khelljyr/Khelljyr.h"

typedef struct	s_Clock
{
  struct tm	t;
  Img		*img;
}		Clock;

static void	format(void *data, char *str, size_t size)
{
  Clock		*c = data;

  // We set the display variable
  snprintf(str, size, "%.2d:%.2d:%.2d", c->t.tm_hour, c->t.tm_min, c->t.tm_sec);
}

static void	format_date(void *data, char *str, size_t size)
{
  Clock		*c = data;

  snprintf(str, size, "%.2d/%.2d %.4d", c->t.tm_mon + 1, c->t.tm_mday, c->t.tm_year + 1900);
}

static void	graphic_fct(Layer *l, GContext *ctx)
{
  Clock		*ptr = USER_PTR;

  // We display the time with custom font
  putstr_format_font(10, format, ptr, FONT_KEY_GOTHIC_28, 30, 0, ctx);

  // We draw the image
  draw_img(ptr->img, ctx);

  putstr_format_font(15, format_date, ptr, FONT_KEY_GOTHIC_28, 15, 135, ctx);

  // Credits
  //putstr("Made with\nKhelljyr Pebble Framework !", 0, 138, ctx);
}

static void	clock_timer(struct tm *time, TimeUnits u)
{
  Clock		*clock_ptr = USER_PTR;

  // We copy the time data to treat it on graphic callback
  memcpy(&clock_ptr->t, time, sizeof(struct tm));

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
  time_t	t = time(NULL);
  Clock		*clock_ptr = data;

  // We create a picture
  clock_ptr->img = create_img_pos(RESOURCE_ID_DRAGON, 40, 45);
  
  // We create a scene in fullscreen
  create_basic_scene_fullscreen(graphic_fct, NULL, unload, NULL);

  // set the time trigger for the time every second
  tick_timer_service_subscribe(SECOND_UNIT, clock_timer);
  clock_timer(localtime(&t), SECOND_UNIT);
}

int		main()
{
  // We create our user data
  Clock		clock_struct;

  // We start our loop with user data
  app_init(&clock_struct, exec);
  return (0);
}
