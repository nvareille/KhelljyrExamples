#include "Khelljyr/Khelljyr.h"

typedef struct	s_Data
{
  int		count;
  Timer		*timer;
}		Data;

static void	second_scene(Layer *layer, GContext *ctx)
{
  Data		*timer = USER_PTR;
  char		disp[64];

  // If count == 100 we stop the timer and destroy it
  if (timer->count == 100)
    clean(timer->timer);

  // Some verbose
  snprintf(disp, sizeof(disp), "The timer has been called %d times", timer->count);
  putstr(disp, 0, 0, ctx);
}

static bool	refresh_second_scene(void *data, Timer *timer)
{
  Data		*ptr = USER_PTR;

  ++ptr->count;
  
  // If count == 10, we tells the timer to activate every 10 ms
  if (ptr->count == 10)
    timer_reschedule(ptr->timer, 10);
  // We refresh the display
  refresh();
  return (true);
}

static bool	second_scene_creation(void *data, Timer *t)
{
  Data		*ptr = USER_PTR;

  // We destroy the actual window
  window_pop();
  
  // We create a new scene
  create_basic_scene(second_scene, NULL, NULL, NULL);

  // We create a new Timer.
  ptr->timer = create_timer(1000, refresh_second_scene, NULL);
  
  // We return false to say the timer is no longer needed
  return (false);
}

static void	first_scene(Layer *l, GContext *ctx)
{
  // Some verbose
  putstr("A Basic scene should appear in 5 seconds ...", 0, 0, ctx);
}

static void	exec()
{
  // We create a basic scene
  create_basic_scene(first_scene, NULL, NULL, NULL);

  // We start a new Timer for 5 seconds
  create_timer(5000, second_scene_creation, NULL);
}

int		main()
{
  Data		timer;

  // We initialize our data
  timer.count = 0;
  
  // We start the program
  app_init(&timer, exec);
  return (0);
}
