#ifndef BOOK_H
#define BOOK_H

#include "main.h"
#include "log.h"

#include "book-save.h"
#include "book-parse.h"

struct Book {
  /* book information */
  gchar *title;         // book title
  gchar *author;        // book author
  gchar *publisher;     // book publisher
  gchar *language;      // book print langauge
  gchar *ISBN;          // book identifier

  gint published;       // book year published
  gint edition;         // book edition / volume
  gint start;           // book start page
  gint pages;           // book print length

  /* file paths */
  gchar *cover;         // book cover location
  gchar *calendar;      // book calendar location

  /* log information */
  struct Log *log;      // book logs

  /* save information */
  gchar *path;
};

/* forward declarations */
struct Book * get_book_active(void);

void new_book(GtkButton *, gpointer);
static struct Book * create_book(GtkWidget *);
static void create_book_file(void);

void select_book(GtkModelButton *, gpointer);
static struct Book * select_book_file(gchar *);

static void free_book(void);
gchar * create_book_path(gchar *);

static void print_book(void);

#endif
