#include "bookr-stack.h"

static GtkBuilder *builder;

void
update_stacks(struct Book *book)
{
  if(!builder) {
    builder = get_builder_builder();
  }

  update_log_stack(book);
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
