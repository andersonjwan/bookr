#ifndef BOOK_H
#define BOOK_H

#include "main.h"

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
};

#endif
