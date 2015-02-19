#include "container_demo.h"

// Our iteration callback. It receive the value and the given pointer
static bool	iter(void *data, void *ptr)
{
  Demo		*demo = ptr;

  putstr(data, 0, demo->nbr * 10, demo->ctx);
  ++demo->nbr;
  
  // We tells the framework to continue
  return (FOREACH_CONTINUE);
}

static void	graphic(Layer *l, GContext *ctx)
{
  Demo		*demo = get_window_data();

  demo->ctx = ctx;
  // We iterate on the given element. It can be a KList or a KStack (use KITERABLE macro)
  foreach(KITERABLE(demo->data), iter, demo);
}

static void	load_list()
{
  KList		*list = create_klist();
  Demo		*demo = alloc(sizeof(Demo));

  // We push some values at the end of the list
  KLIST_PUSH_BACK(list, "0");
  KLIST_PUSH_BACK(list, "1");
  KLIST_PUSH_BACK(list, "2");
  KLIST_PUSH_BACK(list, "3");
  KLIST_PUSH_BACK(list, "4");
  KLIST_PUSH_BACK(list, "5");

  demo->nbr = 0;
  demo->data = list;

  set_window_data(demo);
}

static void	unload_list()
{
  Demo		*demo = get_window_data();

  // We remove some values of the stack, we should use clean_klist
  klist_pop_back(demo->data);
  klist_pop_back(demo->data);
  klist_pop_back(demo->data);
  klist_pop_back(demo->data);
  klist_pop_back(demo->data);
  klist_pop_back(demo->data);
}

static void	load_stack()
{
  KStack	*stack = create_kstack();
  Demo		*demo = alloc(sizeof(Demo));

  // We push some strings on the stack
  KSTACK_PUSH(stack, "0");
  KSTACK_PUSH(stack, "1");
  KSTACK_PUSH(stack, "2");
  KSTACK_PUSH(stack, "3");
  KSTACK_PUSH(stack, "4");
  KSTACK_PUSH(stack, "5");

  demo->nbr = 0;
  demo->data = stack;

  set_window_data(demo);
}

static void	unload_stack()
{
  Demo		*demo = get_window_data();

  // We pop all the values from the stack. It would be better to use clean_kstack
  kstack_pop(demo->data);
  kstack_pop(demo->data);
  kstack_pop(demo->data);
  kstack_pop(demo->data);
  kstack_pop(demo->data);
  kstack_pop(demo->data);
}

static void	exec()
{
  // We create two scenes. One with a stack, the other with a list
  create_basic_scene(graphic, load_stack, unload_stack, NULL);
  create_basic_scene(graphic, load_list, unload_list, NULL);
}

int		main()
{
  app_init(NULL, exec);
  return (0);
}
