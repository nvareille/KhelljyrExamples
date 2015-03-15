#include "Khelljyr/Khelljyr.h"

static void	format(void *data, char *str, size_t size)
{
  int		*nbr = data;

  snprintf(str, size, "%d", *nbr);
}

static void	graphic_add(Layer *l, GContext *ctx)
{
  putstr_format_font(10, format, USER_PTR, FONT_KEY_GOTHIC_28, 0, 0, ctx);
}

static void	load()
{
  int		*nbr = USER_PTR;
  
  *nbr = 0;
}

static void	add_1()
{
  int		*nbr = USER_PTR;

  ++*nbr;
  refresh();
}

static void	sub_1()
{
  int		*nbr = USER_PTR;

  --*nbr;
  refresh();
}

static void	action()
{
  int		*nbr = USER_PTR;

  *nbr = 0;
  vibes_long_pulse();
  refresh();
}

static void	click()
{
  window_single_click_subscribe(BUTTON_ID_UP, add_1);
  window_single_click_subscribe(BUTTON_ID_SELECT, action);
  window_single_click_subscribe(BUTTON_ID_DOWN, sub_1);
}

static void	exec()
{
  create_basic_scene(graphic_add, load, NULL, click);
}

int		main()
{
  int		nbr;

  app_init(&nbr, exec);
  return (0);
}
