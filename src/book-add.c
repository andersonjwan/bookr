#include "book-add.h"

static GtkBuilder *builder = NULL;
static GtkWindow  *dialog  = NULL;

void
show_book_add(void)
{
  if(!builder) {
    builder = gtk_builder_new_from_file("/usr/share/bookr/gui/bookr-book-add.ui");
    gtk_builder_connect_signals(GTK_BUILDER(builder), NULL);
  }

  dialog = get_dialog(builder, "bookr-book-add-dialog");
  gtk_widget_show_all(GTK_WIDGET(dialog));
}

void
hide_book_add(GtkButton *button,
              gpointer   data)
{
  remove_dialog(GTK_WINDOW(dialog));
  gtk_widget_hide(GTK_WIDGET(dialog));
}
