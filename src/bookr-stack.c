#include "bookr-stack.h"

static GtkBuilder *builder;

void
update_stacks(struct Book *book)
{
  if(!builder) {
    builder = get_builder_builder();
  }

  update_log_stack(book);
  update_book_stack(book);
}

static void
update_log_stack(struct Book *book)
{
  update_log_stack_header(book);
}

static void
update_log_stack_header(struct Book *book)
{
  GtkWidget *label;

  /* update title label */
  label = get_widget(builder,"bookr-main-stack-logs-header-label-title");
  gtk_label_set_text(GTK_LABEL(label), book->title);

  /* update author label */
  label = get_widget(builder, "bookr-main-stack-logs-header-label-authors");
  gtk_label_set_text(GTK_LABEL(label), book->author);
}

static void
update_book_stack(struct Book *book)
{
  update_book_stack_log_list(book);
}

static void
update_book_stack_log_list(struct Book *book)
{
  GtkWidget *list;
  list = get_widget(builder,
                    "bookr-main-stack-books-scrolled-viewport-list-box");

  update_book_stack_log_list_clear(list);
  update_book_stack_log_list_build(list, book);

  gtk_widget_show_all(GTK_WIDGET(list));
}

static void
update_book_stack_log_list_clear(GtkWidget *list)
{
  printf("[enter] update_book_stack_log_list_clear\n");

  GList *child, *iter;
  child = gtk_container_get_children(GTK_CONTAINER(list));
  iter = child;

  while(iter) {
    gtk_widget_destroy(GTK_WIDGET(iter->data));
    iter = iter->next;
  }

  g_list_free(g_steal_pointer(&child));

  printf("[exit] update_book_stack_log_list_clear\n");
}

static void
update_book_stack_log_list_build(GtkWidget *list, struct Book *book)
{
  printf("[enter] update_book_stack_log_list_build\n");

  struct Log *iter;
  iter = book->log;

  GtkWidget *child;

  while(iter) {
    child = gtk_button_new_with_label(book->title);
    gtk_list_box_prepend(GTK_LIST_BOX(list), GTK_WIDGET(child));

    iter = iter->next;
  }
}
