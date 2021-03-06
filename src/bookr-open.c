#include "bookr-open.h"

void
bookr_open(void)
{
  bookr_load_book_list();
  if(books) {
    select_book(NULL, ((gchar **) (books->data))[1]);
  }
}

static void
bookr_load_book_list(void)
{
  gchar *prefix, *subpath, *filename;

  prefix   = getenv("HOME");
  subpath  = "/.local/share/bookr/";
  filename = "books-list.data";

  gchar path[strlen(prefix) + strlen(subpath) + strlen(filename) + 1];
  strcpy(path, prefix);
  strcat(path, subpath);
  strcat(path, filename);

  printf("PATH: %s\n", path);

  FILE *file;
  file = fopen(path, "r");

  if(!file) {
    g_printerr("Error %d: Unable to open file: %s\n", 1, path);
    exit(1);
  }

  init_book_lexer(file);
  bookr_parse_book_list();

  reset_book_lexer();
  fclose(file);
}

static void
bookr_parse_book_list()
{
  gchar *token;
  token = peek_key();

  if(*token == '\0')
    return;

  bookr_parse_book();

  if(strcmp(token, "BOOK") == 0) {
    g_free(token);

    bookr_parse_book_list();
  }
  else {
    g_free(token);
  }
}

static void
bookr_parse_book(void)
{
  gchar *title, *path;

  expect_key("BOOK");
  expect_value("BEGIN", NULL);

  title = bookr_parse_book_title();
  path  = bookr_parse_book_path();

  update_book_list(title, path);

  g_free(title);
  g_free(path);

  expect_key("BOOK");
  expect_value("END", NULL);
}

static gchar *
bookr_parse_book_title(void)
{
  expect_key("TITLE");

  gchar *token;
  token = get_value(NULL);

  return token;
}

static gchar *
bookr_parse_book_path(void)
{
  expect_key("PATH");

  gchar *token;
  token = get_value(NULL);

  return token;
}
