#include "Khelljyr/Khelljyr.h"

// The failure callback
static void			fail()
{
  create_basic_text_scene("Fail to push", NULL, NULL);
}

// The news printer callback
static void			print_news(DictionaryIterator *it, void *data)
{
  create_basic_text_scene(dict_find(it, 1)->value->cstring, NULL, NULL);
}

// The callbacks that tells us we set the save
static void			success_save(DictionaryIterator *it, void *data)
{
  create_basic_text_scene("Save Set !", NULL, NULL);
}

// The callbacks that tells us we got the save
static void			success_get_save(DictionaryIterator *it, void *data)
{
  create_basic_text_scene("Save Get !", NULL, NULL);
}

// The callbacks that tells us we don't have a save
static void			fail_get_save(DictionaryIterator *it, void *data)
{
  create_basic_text_scene("No save set on the phone", NULL, NULL);
}

// The array that will contain our functions on message receiving
static void			(*callbacks[])(DictionaryIterator *, void *) =
{
  print_news,
  success_save,
  success_get_save,
  fail_get_save
};

// The message formater function to get the news. The first parameter is a URL, the second is the callback id you previously registered in the callback array.
static void			push_get_news(DictionaryIterator *it, void *data)
{
  message_format(GET_URL, "sd", it, "http://khelljyr.com/news.php", 0);
}

static void			get_news()
{
  message_add(push_get_news, NULL, NULL, fail);
  message_process();
}

// The message formater function to set the save. The first parameter is the save name, the second is the number of fields to save, the next parameters will be the fields to save. The last parameter is a callback to be called once finished.
static void			push_set_save(DictionaryIterator *it, void *data)
{
  message_format(SET_SAVE, "sddd", it, "SAVE", 1, 42, 1);
}

static void			set_save()
{
  message_add(push_set_save, NULL, NULL, fail);
  message_process();
}

// The message formater function to get the save. The first parameter is the save name, the second is the success callback once received (the save was found), the third is the failure callback once received (The save wasn't found)
static void			push_get_save(DictionaryIterator *it, void *data)
{
  message_format(GET_SAVE, "sdd", it, "SAVE", 2, 3);
}

static void			get_save()
{
  message_add(push_get_save, NULL, NULL, fail);
  message_process();
}

// The sections and items of the menu
static const SimpleMenuItem	items[] =
  {
    {"Get Khelljyr news", NULL, NULL, get_news},
    {"Save to phone", NULL, NULL, set_save},
    {"Load from phone", NULL, NULL, get_save},
  };

static const SimpleMenuSection	sections[] =
  {
    {"What to test ?", items, SIZE(items)}
  };

static void			remove_save(DictionaryIterator *it, void *data)
{
  // We create a formated message to delete the save called "save"
  message_format(DELETE_SAVE, "s", it, "SAVE");
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
