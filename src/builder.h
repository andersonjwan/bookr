#ifndef BUILDER_H
#define BUILDER_H

#include "main.h"

#include "book-add.h"
#include "book-edit.h"

#include "log-add.h"

/* forward declarations */
void activate(GtkApplication *, gpointer);
GtkWidget * get_widget(GtkBuilder *, gchar *);
GtkWindow * get_dialog(GtkBuilder *, gchar *);
void destroy_dialog(GtkWindow *);

void show_add(GtkButton *, gpointer);

#endif
