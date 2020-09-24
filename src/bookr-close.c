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
    fprintf(file, "BOOK:BEGIN\n");

    fprintf(file, "TITLE:");
    fprintf(file, "%s\n", ((gchar **) (iter->data))[0]);
    g_free(((gchar **) (iter->data))[0]);

    fprintf(file, "PATH:");
    fprintf(file, "%s\n", ((gchar **) (iter->data))[1]);
    g_free(((gchar **) (iter->data))[1]);

    fprintf(file, "BOOK:END\n");
    g_free(iter->data);

    iter = iter->next;
}

  g_list_free(list);
  fclose(file);
}
