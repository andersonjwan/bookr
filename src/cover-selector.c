#include "cover-selector.h"

static GtkBuilder *builder;
static GtkWindow  *dialog;

static GtkEntry   *entry;

void
show_cover_selector(GtkEntry *widget,
                    gpointer  data)
{
  entry = widget;

  if(!builder) {
    builder = gtk_builder_new_from_file("/usr/share/bookr/gui/bookr-cover-selector.ui");
    gtk_builder_connect_signals(GTK_BUILDER(builder), NULL);
  }

  dialog = get_dialog(builder, "bookr-cover-selector-dialog");
  gtk_widget_show_all(GTK_WIDGET(dialog));
}

void
hide_cover_selector(GtkButton *button,
                    gpointer   data)
{
  remove_dialog(GTK_WINDOW(dialog));
  gtk_widget_hide(GTK_WIDGET(dialog));
}

void
get_cover_selector(GtkButton *button,
                   gpointer   data)
{
  GtkWidget *selector;
  selector = get_widget(builder, "bookr-cover-selector-dialog-file-chooser");

  gchar *file;
  file = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(selector));
  gtk_entry_set_text(GTK_ENTRY(entry), file);

  hide_cover_selector(button, data);
}
