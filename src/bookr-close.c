#include "bookr-close.h"



void
bookr_close(GtkApplication *app,
            gpointer        data)
{
  bookr_write_book_list();
}

static void
bookr_write_book_list(void)
{
  /* create file name */
  gchar *prefix = getenv("HOME");

  gint size;
  size = strlen(prefix) + 34 + 1;

  gchar path[size];
  strcpy(path, prefix);

  strcat(path, "/.local/share/bookr/book-list.data");

  FILE *file;
  file = fopen(path, "w");

  struct BookList *iter;
  iter = get_builder_book_list();

  while(iter) {
    fprintf(file, "%s:%s\n", iter->title, iter->path);
    iter = iter->next;
  }
}
