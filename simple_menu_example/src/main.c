#include "Khelljyr/Khelljyr.h"

// An extern variable to not have a compiler error (change_subtitle and items mekes references to each others)
extern SimpleMenuItem	items[];

// the function that is called by our menu, it changes the subtitle
static void	change_subtitle(int index, void *ctx)
{
  items[index].subtitle = "Pushed Rawr";
  refresh();
}

// Our items in the section
SimpleMenuItem		items[] =
  {
    {"Title1", "Sub", NULL, change_subtitle},
    {"Title2", "Sub", NULL, change_subtitle},
    {"Title3", "Sub", NULL, change_subtitle},
    {"Title4", "Sub", NULL, change_subtitle},
    {"Title5", "Sub", NULL, change_subtitle},
    {"Title6", "Sub", NULL, change_subtitle}
  };

// Our sections used in the menu
static SimpleMenuSection	sections[] =
  {
    {"Titles", items, SIZE(items)}
  };

static void	exec()
{
  // We create a basic menu window
  create_basic_menu_scene(sections, NULL, NULL, SIZE(sections));
}

int		main()
{
  // We start our application
  app_init(NULL, exec);
  return (0);
}
