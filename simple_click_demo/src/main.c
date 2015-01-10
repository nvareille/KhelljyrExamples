#include "Khelljyr/Khelljyr.h"

# define UP "up"
# define SELECT "select"
# define DOWN "down"
# define START "Press a button"

static void	display(Layer *layer, GContext *ctx)
{
  char		**str = USER_PTR;

  putstr(*str, 0, 0, ctx);
}

static void	up(ClickRecognizerRef r, void *ctx)
{
  char		**str = USER_PTR;

  *str = UP;
  refresh();
}

static void	select()
{
  char		**str = USER_PTR;

  *str = SELECT;
  refresh();
}

static void	down()
{
  char		**str = USER_PTR;

  *str = DOWN;
  refresh();
}

static void	click()
{
  window_single_click_subscribe(BUTTON_ID_UP, up);
  window_single_click_subscribe(BUTTON_ID_SELECT, select);
  window_single_click_subscribe(BUTTON_ID_DOWN, down);
}

static void	exec()
{
  create_basic_scene_fullscreen(display, NULL, NULL, click);
}

int		main()
{
  char		*pushed;

  pushed = START;
  app_init(&pushed, exec);
  return (0);
}
