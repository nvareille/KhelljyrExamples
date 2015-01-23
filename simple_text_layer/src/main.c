#include "Khelljyr/Khelljyr.h"

#define TEXT "This is a preview text for Khelljyr's Pebble Framework BasicTextScene\n" \
  "Let's scroll a bit !\n\n\n\n\n\n\n\n" \
  "Hi again !\n" \
  "That's awesome no ?"

static void	exec()
{
  // We create the scene, very easy !
  create_basic_text_scene(TEXT, NULL, NULL);
}

int		main()
{
  // We start the application
  app_init(NULL, exec);
  return (0);
}
