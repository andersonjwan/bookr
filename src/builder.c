#include "builder.h"

static GtkBuilder *builder;

void
activate(GtkApplication *app,
         gpointer        data)
{
  builder = gtk_builder_new_from_file("/usr/share/bookr/gui/bookr.ui");
  gtk_builder_connect_signals(GTK_BUILDER(builder), data);

  GtkWindow *window;
  window = GTK_WINDOW(get_widget(builder, "bookr-window-main"));

  gtk_application_add_window(GTK_APPLICATION(app), GTK_WINDOW(window));
  gtk_widget_show_all(GTK_WIDGET(window));
}

GtkWidget *
get_widget(GtkBuilder *tmp, gchar *identifier)
{
  GObject *object;
  object = gtk_builder_get_object(GTK_BUILDER(tmp), identifier);

  return GTK_WIDGET(object);
}

GtkWindow *
get_dialog(GtkBuilder *tmp, gchar *identifier)
{
  GtkWidget *dialog, *parent;
  dialog = get_widget(tmp, identifier);
  parent = get_widget(builder, "bookr-window-main");

  /* set dialog properties */
  gtk_window_set_transient_for(GTK_WINDOW(dialog), GTK_WINDOW(parent));

  return GTK_WINDOW(dialog);
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
