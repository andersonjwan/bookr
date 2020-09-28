#ifndef BOOKR_CALENDAR_H
#define BOOKR_CALENDAR_H

#include "bookr-main.h"
#include "bookr-book.h"
#include "bookr-log.h"

/* forward declarations */
void write_book_calendar(void);

static void calendar_write_event         (struct Log *);
static void calendar_write_uid           (struct Log *);
static void calendar_write_dtstart       (struct Log *);
static void calendar_write_dtend         (struct Log *);
static void calendar_write_summary       (struct Log *);
static void calendar_write_sequence      (struct Log *);
static void calendar_write_description   (struct Log *);
static void calendar_write_location      (struct Log *);
static void calendar_write_created       (struct Log *);
static void calendar_write_last_modified (struct Log *);

#endif
