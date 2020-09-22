#include "log-add.h"

static GtkBuilder *builder = NULL;
static GtkWindow  *dialog  = NULL;

void
show_log_add(void)
{
  if(!builder) {
    builder = gtk_builder_new_from_file("/usr/share/bookr/gui/bookr-log-add.ui");
    gtk_builder_connect_signals(GTK_BUILDER(builder), NULL);
  }

  dialog = get_dialog(builder, "bookr-log-add-dialog");
  gtk_widget_show_all(GTK_WIDGET(dialog));
}

void
hide_log_add(GtkButton *button,
             gpointer   data)
{
  destroy_dialog(dialog);
  g_object_unref(G_OBJECT(builder));
  builder = NULL;
}
