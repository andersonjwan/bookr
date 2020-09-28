#ifndef BOOK_PARSE_H
#define BOOK_PARSE_H

#include "main.h"

#include "book-lexer.h"

/* forward declarations */
struct Book * parse_book_file(FILE *);

static struct Book * parse_book(void);
static struct Book * parse_book_information(void);

static gchar * parse_book_title(void);
static gchar * parse_book_author(void);
static gchar * parse_book_publisher(void);
static gchar * parse_book_published(void);
static gchar * parse_book_edition(void);
static gchar * parse_book_language(void);
static gchar * parse_book_ISBN(void);
static gchar * parse_book_start_page(void);
static gchar * parse_book_print(void);
static gchar * parse_book_cover(void);
static gchar * parse_book_calendar(void);
static gchar * parse_book_path(void);
static gchar * parse_book_count(void);

static struct Log * parse_book_log(void);
static struct Log * parse_book_log_information(void);

static gchar * parse_book_log_day(void);
static gchar * parse_book_log_month(void);
static gchar * parse_book_log_year(void);
static gchar * parse_book_log_start_hour(void);
static gchar * parse_book_log_start_minute(void);
static gchar * parse_book_log_end_hour(void);
static gchar * parse_book_log_end_minute(void);
static gchar * parse_book_log_start_page(void);
static gchar * parse_book_log_end_page(void);
static gchar * parse_book_log_calendar(void);
static gchar * parse_book_log_number(void);
static gchar * parse_book_log_note(void);

#endif
