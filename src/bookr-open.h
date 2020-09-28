#ifndef BOOKR_OPEN_H
#define BOOKR_OPEN_H

#include "bookr-main.h"
#include "bookr-book-lexer.h"

/* forward declaration(s) */
void bookr_open(void);

static void bookr_load_book_list(void);
static void bookr_parse_book_list(void);
static void bookr_parse_book(void);

static gchar * bookr_parse_book_title(void);
static gchar * bookr_parse_book_path(void);
#endif
