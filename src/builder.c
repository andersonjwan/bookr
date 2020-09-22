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
get_widget(GtkBuilder *builder, gchar *identifier)
{
  GObject *object;
  object = gtk_builder_get_object(GTK_BUILDER(builder), identifier);

  return GTK_WIDGET(object);
}
