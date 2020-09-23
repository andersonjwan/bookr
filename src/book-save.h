#ifndef BOOK_SAVE_H
#define BOOK_SAVE_H

#include "main.h"

#include "book.h"
#include "log.h"

/* forward declarations */
void save_book_file(void);

static void write_book(void);
static void write_book_information(void);
static void write_book_logs(void);
static void write_log(struct Log *);

#endif
