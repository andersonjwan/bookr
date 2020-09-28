#ifndef BOOKR_BUILDER_H
#define BOOKR_BUILDER_H

#include "bookr-main.h"

#include "bookr-book.h"
#include "bookr-book-add.h"
#include "bookr-book-edit.h"

#include "bookr-log-add.h"

#include "bookr-open.h"
#include "bookr-calendar.h"

extern GList *books;

/* forward declarations */
struct BookList * get_builder_book_list(void);
GtkBuilder * get_builder_builder(void);

void activate(GtkApplication *, gpointer);
GtkWidget * get_widget(GtkBuilder *, gchar *);
GtkWindow * get_dialog(GtkBuilder *, gchar *);
void remove_dialog(GtkWindow *);

void update_book_list(gchar *, gchar *);

void show_popover_menu(GtkButton *, gpointer);
void show_popover_books(GtkButton *, gpointer);

void show_add(GtkButton *, gpointer);

#endif
