#ifndef BOOKR_TIME_H
#define BOOKR_TIME_H

#include "bookr-main.h"
#include "bookr-book.h"
#include "bookr-log.h"

/* forward declarations */
struct Log;

guint convert_time(guint, const gchar *);

void generate_date_time_format_start(struct Log *, gchar *);
void generate_date_time_format_end(struct Log *, gchar *);

#endif
