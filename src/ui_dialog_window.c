#include "ui_dialog_window.h"

#ifndef PBL_PLATFORM_APLITE

#define DIALOG_MESSAGE_WINDOW_MARGIN 10

struct UIDialogWindow {
  Window *window;
  TextLayer *label;
  char *message;
  GColor background_color;
  GColor label_color;
};

static void window_load(Window *window) {
  UIDialogWindow *this = window_get_user_data(window);
  Layer *root = window_get_root_layer(window);
  GRect bounds = grect_inset(layer_get_bounds(root), GEdgeInsets(DIALOG_MESSAGE_WINDOW_MARGIN));

  window_set_background_color(window, this->background_color);
  this->label = text_layer_create(bounds);
  text_layer_set_text(this->label, this->message);
  text_layer_set_background_color(this->label, GColorClear);
  text_layer_set_text_color(this->label, this->label_color);
  text_layer_set_text_alignment(this->label, GTextAlignmentCenter);
  text_layer_set_font(this->label, fonts_get_system_font(
      bounds.size.w >= 180 ? FONT_KEY_GOTHIC_24_BOLD : FONT_KEY_GOTHIC_18_BOLD));
  layer_add_child(root, text_layer_get_layer(this->label));
}

static void window_unload(Window *window) {
  UIDialogWindow *this = window_get_user_data(window);
  text_layer_destroy(this->label);
  this->label = NULL;
}

UIDialogWindow* ui_dialog_window_create(char* message, GBitmap* icon) {
  UIDialogWindow *this = malloc(sizeof(UIDialogWindow));
  this->message = message;
  this->label = NULL;
  this->background_color = GColorWhite;
  this->label_color = GColorBlack;
  this->window = window_create();
  window_set_user_data(this->window, this);
  window_set_window_handlers(this->window, (WindowHandlers) {
    .load = window_load,
    .unload = window_unload,
  });
  return this;
}

void ui_dialog_window_destroy(UIDialogWindow* this) {
  window_destroy(this->window);
  free(this);
}

Window* ui_dialog_window_get_window(UIDialogWindow* this) {
  return this->window;
}

void ui_dialog_window_set_background_color(UIDialogWindow* this, const GColor color) {
  this->background_color = color;
}

void ui_dialog_window_set_label_color(UIDialogWindow* this, const GColor color) {
  this->label_color = color;
}

#endif
