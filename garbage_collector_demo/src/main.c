#include "Khelljyr/Khelljyr.h"

#define EXPLANATIONS "On this scene, a lot of memory is allocated. With alloc() function, everything will be freed on the actual window destruction.\n" \
  "Now, it is useless to free your allocations ! But if you want to do it, just use clean() function."

#define DEMONSTRATION "An object is allocated, it will be freed on scene destruction (window_stack_pop works too !)\n" \
  "Check it with \"pebble logs\""

#define CREDITS "Made with Khelljyr Pebble Framework by \n" \
  "Nicolas VAREILLE.\n" \
  "Check it on Github (Khelljyr and KhelljyrExamples)"

static void	draw_explanations(Layer *l, GContext *ctx)
{
  putstr(EXPLANATIONS, 0, 0, ctx);
}

static void	stack_demonstration(Layer *l, GContext *ctx)
{
  putstr(DEMONSTRATION, 0, 0, ctx);
}

static void	draw_credits(Layer *l, GContext *ctx)
{
  putstr(CREDITS, 0, 0, ctx);
}

typedef struct	s_hardcore_ptr
{
  char		c[128];
  int		test;
}		HardcorePtr;

// The function that will be used to free our custom_alloc()
static void	free_hardcore_ptr(void *data)
{
  free(data);
  PRINT("The HardcorePtr is freed !");
}

void dump_memory_manager();

// Basically, a bad code that isn't freed.
static void	loop()
{
  void		*t[3];

  // Credits scene, it will be displayed at end
  create_basic_scene(draw_credits, NULL, NULL, NULL);

  // We create a scene
  create_basic_scene(draw_explanations, NULL, NULL, NULL);

  // Some allocations
  t[0] = alloc(42);
  t[1] = alloc(128);
  t[2] = alloc(1024);

  // Instant clean the allocated memory
  clean(alloc(512));

  // We allocate some memory that will be wasted !
  alloc(2048);

  // We clean the t variable in a random order and we forget t[0]
  clean(t[2]);
  clean(t[1]);

  // We even clean some bad pointers !
  clean((void *)0x424242);

  // We push another scene
  create_basic_scene(stack_demonstration, NULL, NULL, NULL);

  // On custom types, you may use custom_alloc with a function pointer to free it (yup that's the secret) ;p
  custom_alloc(sizeof(HardcorePtr), free_hardcore_ptr);

  // At every window destruction, what have been allocated is freed !
  // Hint: "pebble logs" to verify !
}

int		main()
{
  app_init(NULL, loop);
  return (0);
}
