#include "bookr-stats.h"

guint
bookr_stats_get_current_page(struct Book *book)
{
  if(book) {
    struct Log *iter;
    iter = book->log;

    if(iter) {
      guint max = book->start;

      while(iter) {
        if(max < iter->end_pg)
          max = iter->end_pg;

        iter = iter->next;
      }

      return max;
    }

    return book->start;
  }

  return 0;
}

gdouble
bookr_stats_get_progress(struct Book *book)
{
  if(book) {
    guint total = 0;
    guint count = 0;

    struct Log *iter;
    iter = book->log;

    while(iter) {
      total += bookr_stats_get_page_diff(iter);
      iter = iter->next;
    }

    return ((gdouble) total) / (gdouble) book->pages;
  }

  return 0;
}

guint
bookr_stats_get_page_diff(struct Log *log)
{
  if(log) {
    return log->end_pg - log->start_pg;
  }

  return 0;
}
