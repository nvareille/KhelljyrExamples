#include "Khelljyr/Khelljyr.h"

# define UP "up"
# define SELECT "select"
# define DOWN "down"
# define START "Press a button"

static void	display(Layer *layer, GContext *ctx)
{
  char		**str = USER_PTR;

  // We display what's have been pressed
  putstr(*str, 0, 0, ctx);
}

static void	up()
{
  char		**str = USER_PTR;

  // We set our user data to the good input and then we refresh the screen
  *str = UP;
  refresh();
}

static void	select()
{
  char		**str = USER_PTR;

  // We set our user data to the good input and then we refresh the screen
  *str = SELECT;
  refresh();
}

static void	down()
{
  char		**str = USER_PTR;

  // We set our user data to the good input and then we refresh the screen
  *str = DOWN;
  refresh();
}

static void	click()
{
  // We bind the controls here
  window_single_click_subscribe(BUTTON_ID_UP, up);
  window_single_click_subscribe(BUTTON_ID_SELECT, select);
  window_single_click_subscribe(BUTTON_ID_DOWN, down);
}

static void	exec()
{
  // We create our basic_scene with the click handler
  create_basic_scene_fullscreen(display, NULL, NULL, click);
}

int		main()
{
  char		*pushed;

  // We initialize our string, it will be our user_data
  pushed = START;
  
  // We start the program
  app_init(&pushed, exec);
  return (0);
}
