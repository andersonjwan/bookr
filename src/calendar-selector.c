#include "calendar-selector.h"

static GtkBuilder *builder;
static GtkWindow  *dialog;

void
show_calendar_selector(GtkEntry *entry,
                       gpointer  data)
{
  if(!builder) {
    builder = gtk_builder_new_from_file("/usr/share/bookr/gui/bookr-calendar-selector.ui");
    gtk_builder_connect_signals(GTK_BUILDER(builder), NULL);
  }

  dialog = get_dialog(builder, "bookr-calendar-selector-dialog");
  gtk_widget_show_all(GTK_WIDGET(dialog));
}

void
hide_calendar_selector(GtkButton *button,
                       gpointer   data)
{
  GObject *filter;
  filter = gtk_builder_get_object(GTK_BUILDER(builder),
                                  "bookr-calendar-selector-filter");
  g_object_ref_sink(G_OBJECT(filter));
  g_object_unref(G_OBJECT(filter));

  destroy_dialog(dialog);
  g_object_unref(G_OBJECT(builder));
  builder = NULL;
}
