#ifndef BOOKR_STACK_H
#define BOOKR_STACK_H

#include "bookr-main.h"
#include "bookr-builder.h"

#include "bookr-book.h"

/* forward declarations */
struct Book;

void update_stacks(struct Book *);

static void update_log_stack(struct Book *);
static void update_log_stack_header(struct Book *);

static void update_book_stack(struct Book *);

static void update_book_stack_information(struct Book *);
static void update_book_stack_information_cover(struct Book *);

static void update_book_stack_log_list(struct Book *);
static void update_book_stack_log_list_clear(GtkWidget *);
static void update_book_stack_log_list_build(GtkWidget *, struct Book *);
#endif
