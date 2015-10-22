#include "Khelljyr/Khelljyr.h"

static void	graphic(Layer *layer, GContext *ctx)
{
  putstr("Please press select to start the dictation", 0, 0, ctx);
}

static void	callback(DictationSession *s, DictationSessionStatus status, char *str, void *ctx)
{
  create_basic_text_scene(str,  NULL, NULL);
}

static void	select()
{
  start_dictation();
}

static void	click()
{
  window_single_click_subscribe(BUTTON_ID_SELECT, select);
}

static void	exec()
{
  create_basic_scene(graphic, NULL, NULL, click);
  create_dictation_session(128, callback, NULL, true, true);
}

int		main()
{
  app_init(NULL, exec);
}
