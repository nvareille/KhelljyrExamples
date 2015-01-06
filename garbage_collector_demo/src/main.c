#include "Khelljyr/Khelljyr.h"

// Basically, a bad code that isn't freed.
static void	loop()
{
  void		*t[3];

  // Some allocations
  t[0] = alloc(42);
  t[1] = alloc(128);
  t[2] = alloc(1024);

  // Instant clean the allocated memory
  clean(alloc(512));

  // We allocate some memory that will be wasted !
  alloc(2048);

  // We clean the t variable in a random order
  clean(t[2]);
  clean(t[0]);
  clean(t[1]);

  // We even clean some bad pointers !
  clean((void *)0x424242);

  // At the end of app_init, everything is freed !
  // Hint: "pebble logs" to verify !
}

int		main()
{
  app_init(NULL, loop);
  return (0);
}
