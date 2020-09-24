#include "bookr-close.h"

void
bookr_close(void)
{
  bookr_save_book_list(books);
  return;
}

static void
bookr_save_book_list(GList *list)
{
  FILE *file;
  file = fopen("books-list.data", "w");

  GList *iter, *tmp;

  iter = list, tmp = list;
  while(iter) {
    fprintf(file, "BOOK:");
    fprintf(file, "%s\n", iter->data);
    g_free(iter->data);

    iter = iter->next;
}

  g_list_free(list);
  fclose(file);
}
