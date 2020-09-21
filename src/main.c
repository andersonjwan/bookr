#include "main.h"



static void
activate(GtkApplication *app,
         gpointer        data)
{
  GtkBuilder *builder;
  builder = gtk_builder_new_from_file("/usr/share/bookr/gui/bookr.ui");

  GtkWindow *window;
  window = GTK_WINDOW(gtk_builder_get_object(GTK_BUILDER(builder),
                                               "bookr-main-window"));

  gtk_application_add_window(GTK_APPLICATION(app), GTK_WINDOW(window));
  gtk_widget_show_all(GTK_WIDGET(window));
}

gint
main(gint argc, gchar **argv)
{
  GtkApplication *app;
  int ret;

  app = gtk_application_new("com.github.andersonjwan.bookr", G_APPLICATION_FLAGS_NONE);
  g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);

  ret = g_application_run(G_APPLICATION(app), argc, argv);
  g_object_unref(app);

  return ret;
}
