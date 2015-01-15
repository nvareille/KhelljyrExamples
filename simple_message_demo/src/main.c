#include "Khelljyr/Khelljyr.h"

// The failure callback
static void			fail()
{
  PRINT("Fail to push =/");
}

// Theise functions will add a message to our list of message
static void			add_food(DictionaryIterator *it, void *data)
{
  message_add_string(0, data, it);
}

static void			send_order(DictionaryIterator *it, void *data)
{
  message_add_string(0, "order", it);
}

static void			order_meat()
{
  message_add(add_food, "Meat", NULL, fail);
}

static void			order_fish()
{
  message_add(add_food, "Fish", NULL, fail);
}

static void			order_fruits()
{
  message_add(add_food, "Fruit", NULL, fail);
}

// We order the food
static void			order()
{
  // We add a message to be sent to phone
  message_add(send_order, NULL, NULL, fail);

  // We push our messages to the phone
  message_process();
}

// Graphic callback for the scene
static void			display_success(Layer *layer, GContext *ctx)
{
  putstr("The order is a success ! Check pebble logs !", 0, 0, ctx);
}

// This function will be called when the phone responds us
static void			success_order(DictionaryIterator *it, void *data)
{
  create_basic_scene(display_success, NULL, NULL, NULL);
}

// The sections and items of the menu
static const SimpleMenuItem	items[] =
  {
    {"Meat", NULL, NULL, order_meat},
    {"Fish", NULL, NULL, order_fish},
    {"Fruits", NULL, NULL, order_fruits},
    {"Send command !", NULL, NULL, order}
  };

static const SimpleMenuSection	sections[] =
  {
    {"What does the Dragon wants ?", items, SIZE(items)}
  };

// The array that will contain our functions on message receiving
static void			(*callbacks[])(DictionaryIterator *, void *) =
{
  success_order
};

static void			exec()
{
  // We initialize the messages
  message_init(128, 128, NULL, callbacks);

  // We create the menu
  create_basic_menu_scene(sections, NULL, NULL, SIZE(sections));
}

int				main()
{
  // We start the program
  app_init(NULL, exec);
  return (0);
}
