#include "book-edit.h"

static GtkBuilder *builder = NULL;
static GtkWindow  *dialog  = NULL;

void
show_book_edit(void)
{
  if(!builder) {
    builder = gtk_builder_new_from_file("/usr/share/bookr/gui/bookr-book-edit.ui");
    gtk_builder_connect_signals(GTK_BUILDER(builder), NULL);
  }

  dialog = get_dialog(builder, "bookr-book-edit-dialog");
  gtk_widget_show_all(GTK_WIDGET(dialog));
}

void
hide_book_edit(GtkButton *button,
               gpointer   data)
{
  remove_dialog(GTK_WINDOW(dialog));
  gtk_widget_hide(GTK_WIDGET(dialog));

  clear_book_edit();
}

static void
clear_book_edit(void)
{
  GtkWidget *container;
  container = get_widget(builder, "bookr-book-edit-box-entries");

  GList *child;
  child = gtk_container_get_children(GTK_CONTAINER(container));

  /* clear entry */
  while(child != NULL) {
    gtk_entry_set_text(GTK_ENTRY(child->data), "");

    /* next entry */
    child = child->next;
  }
}
