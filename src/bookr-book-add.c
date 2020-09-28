#include "bookr-book-add.h"

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

  clear_book_add();
}

static void
clear_book_add(void)
{
  GtkWidget *container;
  container = get_widget(builder, "bookr-book-add-box-entries");

  GList *child;
  child = gtk_container_get_children(GTK_CONTAINER(container));

  /* clear entry */
  while(child != NULL) {
    gtk_entry_set_text(GTK_ENTRY(child->data), "");

    /* next entry */
    child = child->next;
  }
}
