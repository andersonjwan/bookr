#ifndef BOOKR_BOOK_LEXER_H
#define BOOKR_BOOK_LEXER_H

#include "bookr-main.h"

#include "bookr-book-parser.h"

/* forward declarations */
void init_book_lexer(FILE *);
void reset_book_lexer(void);

void expect_key(gchar *);
void expect_value(gchar *, gchar *);

gchar * get_key(void);
gchar * get_value(gchar *);

void unget_key(gchar *);
void unget_value(gchar *);

gchar * peek_key(void);
gchar * peek_value(void);

static gint test_delimeter(gchar, gchar *);
#endif
