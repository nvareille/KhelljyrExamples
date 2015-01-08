#include "Khelljyr/Khelljyr.h"

static void	graphic_callback1(Layer *l, GContext *ctx)
{
  // Using USER_PTR allows us to get our datas given to app_init
  Img		**img = USER_PTR;

  // We draw the image (initially, it is located on x: 0 y: 0)
  draw_image(*img, ctx);

  // We draw the image at custom localisation
  draw_image_pos(*img, 80, 50, ctx);

  // Some verbose for the watch
  putstr("<= draw_image", 60, 20, ctx);
  putstr("draw_image_pos =>", 0, 50, ctx);

  // Credits
  putstr("Made easily with\nKhelljyr Framework by\nNicolas VAREILLE", 0, 105, ctx);
}

static void	graphic_callback2(Layer *l, GContext *ctx)
{
  // Using USER_PTR allows us to get our datas given to app_init
  Img		**img = USER_PTR;

  // We draw the image with effect(initially, it is located on x: 0 y: 0)
  draw_image_effect(*img, GCompOpAssignInverted, ctx);

  // We draw the image  effect at custom localisation
  draw_image_effect_pos(*img, GCompOpAssignInverted, 80, 90, ctx);

  // Some verbose for the watch
  putstr("^= draw_image_effect", 0, 60, ctx);
  putstr("draw_image_effect_pos =v", 0, 73, ctx);

}

static void	process(void *data)
{
  // We catch the user data
  Img		**img = data;

  // We create an Image (Before pushing any scenes to keep it until end of app !)
  *img = create_img(RESOURCE_ID_DRAGON);

  // We create scenes
  create_basic_scene(graphic_callback1, NULL, NULL);
  create_basic_scene(graphic_callback2, NULL, NULL);
}

int		main()
{
  // The user datas (it can be anything !)
  Img		*img = NULL;

  // We execute process function on startup
  app_init(&img, process);
}
