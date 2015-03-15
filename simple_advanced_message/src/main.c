#include "Khelljyr/Khelljyr.h"

// The failure callback
static void			fail()
{
  create_basic_text_scene("Fail to push", NULL, NULL);
}

static void			push_get_news(DictionaryIterator *it, void *data)
{
  message_format(ASK_URL, "sd", it, "http://khelljyr.com/news.php", 0);
}

static void			get_news()
{
  message_add(push_get_news, NULL, NULL, fail);
  message_process();
}

// The sections and items of the menu
static const SimpleMenuItem	items[] =
  {
    {"Get Khelljyr news", NULL, NULL, get_news},
    {"Save to phone", NULL, NULL, NULL},
    {"Load from phone", NULL, NULL, NULL},
  };

static const SimpleMenuSection	sections[] =
  {
    {"What to test ?", items, SIZE(items)}
  };

static void			print_news(DictionaryIterator *it, void *data)
{
  create_basic_text_scene(dict_find(it, 1)->value->cstring, NULL, NULL);
}

// The array that will contain our functions on message receiving
static void			(*callbacks[])(DictionaryIterator *, void *) =
{
  print_news,
};

static void			remove_save(DictionaryIterator *it, void *data)
{
  // We create a formated message to delete the save called "save"
  message_format(DELETE_SAVE, "s", it, "save");
}

static void			start()
{
  // We remove the previous window
  window_pop();
  
  // We create the menu
  create_basic_menu_scene(sections, NULL, NULL, SIZE(sections));
}

static void			graphic(Layer *l, GContext *ctx)
{
  putstr("LOADING ...", 0, 0, ctx);
}

static void			exec()
{
  // We initialize the messages
  message_init(512, 512, NULL, callbacks);

  // We create a waiting scene
  create_basic_scene(graphic, NULL, NULL, NULL);

  // We clean the phone save
  message_add(remove_save, NULL, start, fail);
  
  // We push the messages
  message_process();
}

int				main()
{
  // We start the program
  app_init(NULL, exec);
  return (0);
}
