#include "book-add.h"

static GtkBuilder *builder;
static GtkWindow  *dialog;

void
show_book_add(void)
{
  builder = gtk_builder_new_from_file("/usr/share/bookr/gui/bookr-book-add.ui");
  gtk_builder_connect_signals(GTK_BUILDER(builder), NULL);

  dialog = get_dialog(builder, "bookr-book-add-dialog");
  gtk_widget_show_all(GTK_WIDGET(dialog));
}

void
hide_book_add(GtkButton *button,
              gpointer   data)
{
  destroy_dialog(dialog);
}
