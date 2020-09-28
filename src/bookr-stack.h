#ifndef BOOKR_STACK_H
#define BOOKR_STACK_H

#include "main.h"
#include "builder.h"

#include "book.h"

/* forward declarations */
struct Book;

void update_stacks(struct Book *);

static void update_log_stack(struct Book *);
static void update_log_stack_header(struct Book *);
#endif
