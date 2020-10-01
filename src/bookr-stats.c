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
