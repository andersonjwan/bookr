#include "book-edit.h"

static GtkBuilder *builder;
static GtkWindow  *dialog;

void
show_book_edit(void)
{
  builder = gtk_builder_new_from_file("/usr/share/bookr/gui/bookr-book-edit.ui");
  gtk_builder_connect_signals(GTK_BUILDER(builder), NULL);

  dialog = get_dialog(builder, "bookr-book-edit-dialog");
  gtk_widget_show_all(GTK_WIDGET(dialog));
}

void
hide_book_edit(GtkButton *button,
              gpointer   data)
{
  gtk_widget_destroy(GTK_WIDGET(dialog));
}
