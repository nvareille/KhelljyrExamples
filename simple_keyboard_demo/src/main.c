#include "Khelljyr/Khelljyr.h"

static void	graphic(Layer *l, GContext *ctx)
{
  // We get the data on the window
  char		*str = get_window_data();

  // Some verbose
  putstr("You typed:", 0, 0, ctx);
  putstr(str, 0, 12, ctx);
}

static void	callback_keyboard(Keyboard *k)
{
  char		*str;

  // We create a new scene
  create_basic_scene(graphic, NULL, NULL, NULL);
  
  // We take some memory to copy our string
  str = alloc(15);

  // We copy our string
  strncpy(str, k->str, k->size);
  
  // We set the data on the window
  set_window_data(str);
}

static void	exec()
{
  // We create the Keyboard with "Rawr !" already typed
  create_basic_keyboard_scene("Rawr", 15, callback_keyboard);
}

int		main()
{
  // We start the application
  app_init(NULL, exec);

  return (0);
}
