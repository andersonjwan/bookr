#include "book-parser.h"

extern FILE *input;

void
parse_book_file(FILE *file)
{
  init_book_lexer(file);

  parse_book();
  printf("BOOK PARSED\n");
  return;
}

static void
parse_book(void)
{
  expect_key("BOOK");
  expect_value("BEGIN", NULL);

  parse_book_information();

  gchar *token;
  token = peek_key();

  if(strcmp(token, "LOG") == 0) {
    free(token);
    parse_book_log();
  }
  else {
    free(token);
  }

  expect_key("BOOK");
  expect_value("END", NULL);
}

static void
parse_book_information(void)
{
  parse_book_title();
  parse_book_author();
  parse_book_publisher();
  parse_book_published();
  parse_book_edition();
  parse_book_language();
  parse_book_ISBN();
  parse_book_start_page();
  parse_book_print();
  parse_book_cover();
  parse_book_calendar();
  parse_book_path();
}

static void
parse_book_title(void)
{
  expect_key("TITLE");

  gchar *token;
  token = get_value(NULL);
}

static void
parse_book_author(void)
{
  expect_key("AUTHOR");

  gchar *token;
  token = get_value(NULL);
}

static void
parse_book_publisher(void)
{
  expect_key("PUBLISHER");

  gchar *token;
  token = get_value(NULL);
}

static void
parse_book_published(void)
{
  expect_key("PUBLISHED");

  gchar *token;
  token = get_value(NULL);
}

static void
parse_book_edition(void)
{
  expect_key("EDITION");

  gchar *token;
  token = get_value(NULL);
}

static void
parse_book_language(void)
{
  expect_key("LANGUAGE");

  gchar *token;
  token = get_value(NULL);
}

static void
parse_book_ISBN(void)
{
  expect_key("ISBN");

  gchar *token;
  token = get_value(NULL);
}

static void
parse_book_start_page(void)
{
  expect_key("STARTPAGE");

  gchar *token;
  token = get_value(NULL);
}

static void
parse_book_print(void)
{
  expect_key("PRINT");

  gchar *token;
  token = get_value(NULL);
}

static void
parse_book_cover(void)
{
  expect_key("COVERPATH");

  gchar *token;
  token = get_value(NULL);
}

static void
parse_book_calendar(void)
{
  expect_key("ICALPATH");

  gchar *token;
  token = get_value(NULL);
}

static void
parse_book_path(void)
{
  expect_key("FILEPATH");

  gchar *token;
  token = get_value(NULL);
}

static void
parse_book_log(void)
{
  expect_key("LOG");
  expect_value("BEGIN", NULL);

  parse_book_log_information();

  expect_key("LOG");
  expect_value("END", NULL);

  gchar *token;
  token = peek_key();

  if(strcmp(token, "LOG") == 0) {
    g_free(token);

    parse_book_log();
  }
}

static void
parse_book_log_information(void)
{
  parse_book_log_day();
  parse_book_log_month();
  parse_book_log_year();

  parse_book_log_start_hour();
  parse_book_log_start_minute();
  parse_book_log_end_hour();
  parse_book_log_end_minute();

  parse_book_log_start_page();
  parse_book_log_end_page();

  parse_book_log_note();
}

static void
parse_book_log_day(void)
{
  expect_key("DAY");

  gchar *token;
  token = get_value(";");
}

static void
parse_book_log_month(void)
{
  expect_key("MONTH");

  gchar *token;
  token = get_value(";");
}

static void
parse_book_log_year(void)
{
  expect_key("YEAR");

  gchar *token;
  token = get_value(";");
}

static void
parse_book_log_start_hour(void)
{
  expect_key("STARTHOUR");

  gchar *token;
  token = get_value(";");
}

static void
parse_book_log_start_minute(void)
{
  expect_key("STARTMIN");

  gchar *token;
  token = get_value(";");
}

static void
parse_book_log_end_hour(void)
{
  expect_key("ENDHOUR");

  gchar *token;
  token = get_value(";");
}

static void
parse_book_log_end_minute(void)
{
  expect_key("ENDMIN");

  gchar *token;
  token = get_value(";");
}

static void
parse_book_log_start_page(void)
{
  expect_key("STARTPAGE");

  gchar *token;
  token = get_value(";");
}

static void
parse_book_log_end_page(void)
{
  expect_key("ENDPAGE");

  gchar *token;
  token = get_value(";");
}

static void
parse_book_log_note(void)
{
  expect_key("NOTES");

  gchar *token;
  token = get_value(";");
}
