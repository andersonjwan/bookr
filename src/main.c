#include "main.h"

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
