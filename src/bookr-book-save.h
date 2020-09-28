#ifndef BOOKR_BOOK_SAVE_H
#define BOOKR_BOOK_SAVE_H

#include "bookr-main.h"

#include "bookr-book.h"
#include "bookr-log.h"

/* forward declarations */
struct Log;

void save_book_file(void);

static void write_book(void);
static void write_book_information(void);
static void write_book_logs(void);
static void write_log(struct Log *);

#endif
