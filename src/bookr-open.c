#include "bookr-open.h"

void
bookr_open(void)
{
  printf("[enter] bookr_open\n");

  bookr_load_book_list();

  printf("[exit] bookr_open\n");
}

static void
bookr_load_book_list(void)
{
  printf("[enter] bookr_load_book_list\n");

  FILE *file;
  file = fopen("books-list.data", "r");

  if(file) {
    init_book_lexer(file);
    bookr_parse_book_list();

    reset_book_lexer();
    fclose(file);
  }

  printf("[exit] bookr_load_book_list\n");
}

static void
bookr_parse_book_list()
{
  printf("[enter] bookr_parse_book_list\n");

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

  printf("[exit] bookr_parse_book_list\n");
}

static void
bookr_parse_book(void)
{
  printf("[enter] bookr_parse_book\n");
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

  printf("[exit] bookr_parse_book\n");
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
