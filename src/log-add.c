#include "log-add.h"

static GtkBuilder *builder = NULL;
static GtkWindow  *dialog  = NULL;

GtkBuilder *
get_log_add_builder(void)
{
  return builder;
}

void
show_log_add(void)
{
  if(!builder) {
    builder = gtk_builder_new_from_file("/usr/share/bookr/gui/bookr-log-add.ui");
    gtk_builder_connect_signals(GTK_BUILDER(builder), NULL);
  }

  dialog = get_dialog(builder, "bookr-log-add-dialog");
  gtk_widget_show_all(GTK_WIDGET(dialog));
}

void
hide_log_add(GtkButton *button,
             gpointer   data)
{
  remove_dialog(GTK_WINDOW(dialog));
  gtk_widget_hide(GTK_WIDGET(dialog));

  clear_log_add();
}

static void
clear_log_add(void)
{
  GtkWidget *widget;

  /* clear start time */
  widget = get_widget(builder, "bookr-log-add-time-entry-start-hour");
  gtk_entry_set_text(GTK_ENTRY(widget), "");
  widget = get_widget(builder, "bookr-log-add-time-entry-start-minute");
  gtk_entry_set_text(GTK_ENTRY(widget), "");
  widget = get_widget(builder, "bookr-log-add-time-button-start");
  gtk_button_set_label(GTK_BUTTON(widget), "AM");

  /* clear end time */
  widget = get_widget(builder, "bookr-log-add-time-entry-end-hour");
  gtk_entry_set_text(GTK_ENTRY(widget), "");
  widget = get_widget(builder, "bookr-log-add-time-entry-end-minute");
  gtk_entry_set_text(GTK_ENTRY(widget), "");
  widget = get_widget(builder, "bookr-log-add-time-button-end");
  gtk_button_set_label(GTK_BUTTON(widget), "AM");

  /* clear pages */
  widget = get_widget(builder, "bookr-log-add-pages-entry-start-page");
  gtk_entry_set_text(GTK_ENTRY(widget), "");
  widget = get_widget(builder, "bookr-log-add-pages-entry-end-page");
  gtk_entry_set_text(GTK_ENTRY(widget), "");

  /* clear notes */
  GObject *object;
  object = gtk_builder_get_object(GTK_BUILDER(builder),
                                  "bookr-log-add-notes-text-buffer");
  gtk_text_buffer_set_text(GTK_TEXT_BUFFER(object), "", 0);
}
