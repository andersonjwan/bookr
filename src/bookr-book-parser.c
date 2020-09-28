#include "bookr-book-parser.h"

struct Book *
parse_book_file(FILE *file)
{
  init_book_lexer(file);

  struct Book *active;
  active = parse_book();

  reset_book_lexer();

  return active;
}

struct Book *
parse_book(void)
{
  struct Book *new;
  new = NULL;

  expect_key("BOOK");
  expect_value("BEGIN", NULL);

  new = parse_book_information();
  new->log = NULL;

  gchar *token;
  token = peek_key();

  if(strcmp(token, "LOG") == 0) {
    free(token);

    new->log = parse_book_log();
  }
  else {
    free(token);
  }

  expect_key("BOOK");
  expect_value("END", NULL);

  return new;
}

static struct Book *
parse_book_information(void)
{
  struct Book *new;
  new = (struct Book *) malloc(sizeof(struct Book));

  gchar *data;

  data = parse_book_title();
  new->title = (gchar *) malloc(sizeof(gchar) * strlen(data) + 1);
  strcpy(new->title, data);
  g_free(data);

  data = parse_book_author();
  new->author = (gchar *) malloc(sizeof(gchar) * strlen(data) + 1);
  strcpy(new->author, data);
  g_free(data);

  data = parse_book_publisher();
  new->publisher = (gchar *) malloc(sizeof(gchar) * strlen(data) + 1);
  strcpy(new->publisher, data);
  g_free(data);

  data = parse_book_published();
  new->published = atoi(data);
  g_free(data);

  data = parse_book_edition();
  new->edition = atoi(data);
  g_free(data);

  data = parse_book_language();
  new->language = (gchar *) malloc(sizeof(gchar) * strlen(data) + 1);
  strcpy(new->language, data);
  g_free(data);

  data = parse_book_ISBN();
  new->isbn = (gchar *) malloc(sizeof(gchar) * strlen(data) + 1);
  strcpy(new->isbn, data);
  free(data);

  data = parse_book_start_page();
  new->start = atoi(data);
  free(data);

  data = parse_book_print();
  new->pages = atoi(data);
  free(data);

  data = parse_book_cover();
  new->cover = (gchar *) malloc(sizeof(gchar) * strlen(data) + 1);
  strcpy(new->cover, data);
  free(data);

  data = parse_book_calendar();
  new->calendar = (gchar *) malloc(sizeof(gchar) * strlen(data) + 1);
  strcpy(new->calendar, data);
  free(data);

  data = parse_book_path();
  new->path = (gchar *) malloc(sizeof(gchar) * strlen(data) + 1);
  strcpy(new->path, data);
  free(data);

  data = parse_book_count();
  new->count = atoi(data);
  free(data);

  return new;
}

static gchar *
parse_book_title(void)
{
  expect_key("TITLE");

  gchar *token;
  token = get_value(NULL);

  return token;
}

static gchar *
parse_book_author(void)
{
  expect_key("AUTHOR");

  gchar *token;
  token = get_value(NULL);

  return token;
}

static gchar *
parse_book_publisher(void)
{
  expect_key("PUBLISHER");

  gchar *token;
  token = get_value(NULL);

  return token;
}

static gchar *
parse_book_published(void)
{
  expect_key("PUBLISHED");

  gchar *token;
  token = get_value(NULL);

  return token;
}

static gchar *
parse_book_edition(void)
{
  expect_key("EDITION");

  gchar *token;
  token = get_value(NULL);

  return token;
}

static gchar *
parse_book_language(void)
{
  expect_key("LANGUAGE");

  gchar *token;
  token = get_value(NULL);

  return token;
}

static gchar *
parse_book_ISBN(void)
{
  expect_key("ISBN");

  gchar *token;
  token = get_value(NULL);

  return token;
}

static gchar *
parse_book_start_page(void)
{
  expect_key("STARTPAGE");

  gchar *token;
  token = get_value(NULL);

  return token;
}

static gchar *
parse_book_print(void)
{
  expect_key("PRINT");

  gchar *token;
  token = get_value(NULL);

  return token;
}

static gchar *
parse_book_cover(void)
{
  expect_key("COVERPATH");

  gchar *token;
  token = get_value(NULL);

  return token;
}

static gchar *
parse_book_calendar(void)
{
  expect_key("ICALPATH");

  gchar *token;
  token = get_value(NULL);

  return token;
}

static gchar *
parse_book_path(void)
{
  expect_key("FILEPATH");

  gchar *token;
  token = get_value(NULL);

  return token;
}

static gchar *
parse_book_count(void)
{
  expect_key("LOGSCOUNT");

  gchar *token;
  token = get_value(NULL);

  return token;
}

static struct Log *
parse_book_log(void)
{
  struct Log *new;

  expect_key("LOG");
  expect_value("BEGIN", NULL);

  new = parse_book_log_information();
  new->prev = NULL;
  new->next = NULL;

  expect_key("LOG");
  expect_value("END", NULL);

  gchar *token;
  token = peek_key();

  if(strcmp(token, "LOG") == 0) {
    g_free(token);

    struct Log *tmp;
    tmp = parse_book_log();

    new->next = tmp;
    tmp->prev = new;
  }

  return new;
}

static struct Log *
parse_book_log_information(void)
{
  struct Log *new;
  new = (struct Log *) malloc(sizeof(struct Log));

  gchar *data;

  data = parse_book_log_day();
  new->day = atoi(data);
  g_free(data);

  data = parse_book_log_month();
  new->month = atoi(data);
  g_free(data);

  data = parse_book_log_year();
  new->year = atoi(data);
  g_free(data);

  data = parse_book_log_start_hour();
  new->start_hr = atoi(data);
  g_free(data);

  data = parse_book_log_start_minute();
  new->start_min = atoi(data);
  g_free(data);

  data = parse_book_log_end_hour();
  new->end_hr = atoi(data);
  g_free(data);

  data = parse_book_log_end_minute();
  new->end_min = atoi(data);
  g_free(data);

  data = parse_book_log_start_page();
  new->start_pg = atoi(data);
  g_free(data);

  data = parse_book_log_end_page();
  new->end_pg = atoi(data);
  g_free(data);

  data = parse_book_log_calendar();
  new->calendar = atoi(data);
  g_free(data);

  data = parse_book_log_number();
  new->calendar = atoi(data);
  g_free(data);

  data = parse_book_log_note();
  new->note = (gchar *) malloc(sizeof(gchar) * strlen(data) + 1);
  strcpy(new->note, data);
  g_free(data);

  return new;
}

static gchar *
parse_book_log_day(void)
{
  expect_key("DAY");

  gchar *token;
  token = get_value(";");

  return token;
}

static gchar *
parse_book_log_month(void)
{
  expect_key("MONTH");

  gchar *token;
  token = get_value(";");

  return token;
}

static gchar *
parse_book_log_year(void)
{
  expect_key("YEAR");

  gchar *token;
  token = get_value(";");

  return token;
}

static gchar *
parse_book_log_start_hour(void)
{
  expect_key("STARTHOUR");

  gchar *token;
  token = get_value(";");

  return token;
}

static gchar *
parse_book_log_start_minute(void)
{
  expect_key("STARTMIN");

  gchar *token;
  token = get_value(";");

  return token;
}

static gchar *
parse_book_log_end_hour(void)
{
  expect_key("ENDHOUR");

  gchar *token;
  token = get_value(";");

  return token;
}

static gchar *
parse_book_log_end_minute(void)
{
  expect_key("ENDMIN");

  gchar *token;
  token = get_value(";");

  return token;
}

static gchar *
parse_book_log_start_page(void)
{
  expect_key("STARTPAGE");

  gchar *token;
  token = get_value(";");

  return token;
}

static gchar *
parse_book_log_end_page(void)
{
  expect_key("ENDPAGE");

  gchar *token;
  token = get_value(";");

  return token;
}

static gchar *
parse_book_log_calendar(void)
{
  expect_key("CALENDAR");

  gchar *token;
  token = get_value(";");

  return token;
}

static gchar *
parse_book_log_number(void)
{
  expect_key("NUMBER");

  gchar *token;
  token = get_value(";");

  return token;
}

static gchar *
parse_book_log_note(void)
{
  expect_key("NOTES");

  gchar *token;
  token = get_value(";");

  return token;
}
