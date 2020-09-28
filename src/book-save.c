#include "book-save.h"

static struct Book *active;
static FILE *file;

void
save_book_file(void)
{
  active = get_book_active();
  file = fopen(active->path, "w");

  write_book();

  /* close file */
  fclose(file);
}

static void
write_book(void)
{
  fprintf(file, "BOOK:BEGIN\n");

  write_book_information();
  write_book_logs();

  fprintf(file, "BOOK:END\n");
}

static void
write_book_information(void)
{
  fprintf(file, "TITLE:%s\n",       active->title);
  fprintf(file, "AUTHOR:%s\n",      active->author);
  fprintf(file, "PUBLISHER:%s\n",   active->publisher);
  fprintf(file, "PUBLISHED:%04d\n", active->published);
  fprintf(file, "EDITION:%02d\n",   active->edition);
  fprintf(file, "LANGUAGE:%s\n",    active->language);
  fprintf(file, "ISBN:%s\n",        active->isbn);
  fprintf(file, "STARTPAGE:%05d\n", active->start);
  fprintf(file, "PRINT:%05d\n",     active->pages);
  fprintf(file, "COVERPATH:%s\n",   active->cover);
  fprintf(file, "ICALPATH:%s\n",    active->calendar);
  fprintf(file, "FILEPATH:%s\n",    active->path);
  fprintf(file, "LOGSCOUNT:%05d\n", active->count);
}

static void
write_book_logs(void)
{
  struct Log *iter;
  iter = active->log;

  while(iter) {
    write_log(iter);
    iter = iter->next;
  }
}

static void
write_log(struct Log *log)
{
  fprintf(file, "LOG:BEGIN\n");

  fprintf(file, "DAY:%02d;", log->day);
  fprintf(file, "MONTH:%02d;", log->month);
  fprintf(file, "YEAR:%04d\n", log->year);

  fprintf(file, "STARTHOUR:%02d;", log->start_hr);
  fprintf(file, "STARTMIN:%02d;",  log->start_min);
  fprintf(file, "ENDHOUR:%02d;",   log->end_hr);
  fprintf(file, "ENDMIN:%02d\n",   log->end_min);

  fprintf(file, "STARTPAGE:%05d;", log->start_pg);
  fprintf(file, "ENDPAGE:%05d\n", log->end_pg);

  fprintf(file, "CALENDAR:%02d\n", log->calendar);
  fprintf(file, "NUMBER:%02d\n", log->number);
  fprintf(file, "NOTES:%s\n", log->note);

  fprintf(file, "LOG:END\n");
}
