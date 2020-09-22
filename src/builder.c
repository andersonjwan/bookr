#include "builder.h"

static GtkApplication *bookr   = NULL;
static GtkBuilder     *builder = NULL;

void
activate(GtkApplication *app,
         gpointer        data)
{
  if(!bookr) {
    bookr = GTK_APPLICATION(app);
  }

  if(!builder) {
    builder = gtk_builder_new_from_file("/usr/share/bookr/gui/bookr.ui");
    gtk_builder_connect_signals(GTK_BUILDER(builder), data);
  }

  GtkWindow *window;
  window = GTK_WINDOW(get_widget(builder, "bookr-window-main"));

  gtk_application_add_window(GTK_APPLICATION(app), GTK_WINDOW(window));
  gtk_widget_show_all(GTK_WIDGET(window));
}

GtkWidget *
get_widget(GtkBuilder *builder, gchar *identifier)
{
  GObject *object;
  object = gtk_builder_get_object(GTK_BUILDER(builder), identifier);

  return GTK_WIDGET(object);
}

GtkWindow *
get_dialog(GtkBuilder *builder, gchar *identifier)
{
  GtkWindow *dialog, *parent;
  dialog = GTK_WINDOW(get_widget(builder, identifier));
  parent = gtk_application_get_active_window(GTK_APPLICATION(bookr));

  /* set dialog properties */
  gtk_window_set_transient_for(GTK_WINDOW(dialog), GTK_WINDOW(parent));
  gtk_application_add_window(GTK_APPLICATION(bookr), GTK_WINDOW(dialog));

  return GTK_WINDOW(dialog);
}

void
remove_dialog(GtkWindow *dialog)
{
  gtk_application_remove_window(GTK_APPLICATION(bookr), GTK_WINDOW(dialog));
}

void
show_add(GtkButton *button,
         gpointer   data)
{
  GtkWidget *stack;
  stack = get_widget(builder, "bookr-main-stack");

  const gchar *visible;
  visible = gtk_stack_get_visible_child_name(GTK_STACK(stack));

  if(strcmp(visible, "books") == 0) {
    show_book_add();
  }
  else if(strcmp(visible, "logs") == 0) {
    show_log_add();
  }
}

void
show_edit(GtkButton *button,
          gpointer   data)
{
  GtkWidget *stack;
  stack = get_widget(builder, "bookr-main-stack");

  const gchar *visible;
  visible = gtk_stack_get_visible_child_name(GTK_STACK(stack));

  if(strcmp(visible, "books") == 0) {
    show_book_edit();
  }
  else if(strcmp(visible, "logs") == 0) {
    // TODO
  }
}

void
show_popover_menu(GtkButton *button,
                  gpointer   data)
{
  GtkWidget *popover;
  popover = get_widget(builder, "bookr-main-popover-menu");

  gtk_popover_popup(GTK_POPOVER(popover));
  gtk_widget_show_all(GTK_WIDGET(popover));
}

void
show_popover_books(GtkButton *button,
                   gpointer   data)
{
  GtkWidget *popover;
  popover = get_widget(builder, "bookr-main-popover-books-list");

  gtk_popover_popup(GTK_POPOVER(popover));
  gtk_widget_show_all(GTK_WIDGET(popover));
}

void
update_book_list(gchar *title)
{
  GtkWidget *container;
  container = get_widget(builder, "bookr-main-popover-books-list-box");

  GtkWidget *button;
  button = gtk_widget_new(GTK_TYPE_MODEL_BUTTON,
                          "text", title,
                          NULL);

  gtk_box_pack_start(GTK_BOX(container), GTK_WIDGET(button),
                     FALSE, FALSE, 0);

  printf("EXITED\n");
}
