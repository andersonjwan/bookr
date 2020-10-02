#ifndef BOOKR_STATS_H
#define BOOKR_STATS_H

#include "bookr-main.h"
#include "bookr-book.h"

/* forward declarations */
struct Book;
struct Log;

guint bookr_stats_get_current_page(struct Book *);
gdouble bookr_stats_get_progress(struct Book *);
guint bookr_stats_get_page_diff(struct Log *);
#endif
