#include "bookr-open.h"

void
bookr_open(void)
{
  bookr_load_book_list();
}

static void
bookr_load_book_list(void)
{
  FILE *file;
  file = fopen("books-list.data", "r");

  if(file) {
    init_book_lexer(file);
    bookr_parse_book_list();

    reset_book_lexer();
    fclose(file);
  }
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

  update_book_list(title);

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
