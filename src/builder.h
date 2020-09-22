#ifndef BUILDER_H
#define BUILDER_H

#include "main.h"

#include "book.h"
#include "book-add.h"
#include "book-edit.h"

#include "log-add.h"

/* forward declarations */
void activate(GtkApplication *, gpointer);
GtkWidget * get_widget(GtkBuilder *, gchar *);
GtkWindow * get_dialog(GtkBuilder *, gchar *);
void remove_dialog(GtkWindow *);

void update_book_list(gchar *);

void show_popover_menu(GtkButton *, gpointer);
void show_popover_books(GtkButton *, gpointer);

void show_add(GtkButton *, gpointer);

#endif
