#pragma once
#include <pebble.h>

// Minimal replacement for the pebble-ui-dialog-window package,
// which ships no binary for emery.
typedef struct UIDialogWindow UIDialogWindow;

UIDialogWindow* ui_dialog_window_create(char* message, GBitmap* icon);
void ui_dialog_window_destroy(UIDialogWindow* this);
Window* ui_dialog_window_get_window(UIDialogWindow* this);
void ui_dialog_window_set_background_color(UIDialogWindow* this, const GColor color);
void ui_dialog_window_set_label_color(UIDialogWindow* this, const GColor color);
