#include "builder.h"

static GtkBuilder *bookr_builder;

void
activate(GtkApplication *app,
         gpointer        data)
{
  GtkBuilder *builder;
  builder = gtk_builder_new_from_file("/usr/share/bookr/gui/bookr.ui");
  bookr_builder = builder;

  GtkWindow *window;
  window = GTK_WINDOW(gtk_builder_get_object(GTK_BUILDER(builder),
                                             "bookr-main-window"));

  gtk_application_add_window(GTK_APPLICATION(app), GTK_WINDOW(window));
  gtk_widget_show_all(GTK_WIDGET(window));
}
