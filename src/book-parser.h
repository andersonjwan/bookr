#ifndef BOOK_PARSE_H
#define BOOK_PARSE_H

#include "main.h"

#include "book-lexer.h"

/* forward declarations */
void parse_book_file(FILE *);

static void parse_book(void);
static void parse_book_information(void);

static void parse_book_title(void);
static void parse_book_author(void);
static void parse_book_publisher(void);
static void parse_book_published(void);
static void parse_book_edition(void);
static void parse_book_language(void);
static void parse_book_ISBN(void);
static void parse_book_start_page(void);
static void parse_book_print(void);
static void parse_book_cover(void);
static void parse_book_calendar(void);
static void parse_book_path(void);

static void parse_book_log(void);
static void parse_book_log_information(void);

static void parse_book_log_day(void);
static void parse_book_log_month(void);
static void parse_book_log_year(void);
static void parse_book_log_start_hour(void);
static void parse_book_log_start_minute(void);
static void parse_book_log_end_hour(void);
static void parse_book_log_end_minute(void);
static void parse_book_log_start_page(void);
static void parse_book_log_end_page(void);
static void parse_book_log_note(void);

#endif
