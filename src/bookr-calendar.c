#include "bookr-calendar.h"

static FILE *file;
static struct Book *active;

void
write_book_calendar(void)
{
  active = get_book_active();

  if(active) {
    file = fopen(active->calendar, "r+");

    if(!file) {
      g_printerr("Error %d: Unable to open file: %s\n",
                 1, active->calendar);
      exit(1);
    }

    gchar character;
    long int new = 0, position;

    do {
      character = getc(file);

      if(character == '\n') {
        position = new;
        new = ftell(file);
      }
    }
    while(character != EOF);

    fseek(file, position, SEEK_SET);

    struct Log *curr;
    curr = active->log;

    while(curr) {
      if(!(curr->calendar)) {
        calendar_write_event(curr);
        curr->calendar = TRUE;
      }

      /* next log */
      curr = curr->next;
    }

    fprintf(file, "END:VCALENDAR\n");
    fclose(file);
  }
}
static void
calendar_write_event(struct Log *log)
{
  fprintf(file, "BEGIN:VEVENT\n");

  calendar_write_uid(log);
  calendar_write_dtstart(log);
  calendar_write_dtend(log);
  calendar_write_summary(log);
  calendar_write_sequence(log);
  calendar_write_description(log);
  calendar_write_location(log);
  calendar_write_created(log);
  calendar_write_last_modified(log);

  fprintf(file, "END:VEVENT\n");
}

static void
calendar_write_uid(struct Log *log)
{
  fprintf(file, "UID:");

  gint isbn, suffix;
  isbn   = strlen(active->isbn);
  suffix = strlen("com.github.andersonjwan.bookr");

  gchar uid[isbn + 6 + 1 + suffix + 1];
  generate_log_uid(log, uid);

  fprintf(file, "%s\n", uid);
}

static void
calendar_write_dtstart(struct Log *log)
{
  fprintf(file, "DTSTART;TZID=/freeassociation.sourceforge.net/America/Phoenix:");

  gchar datetime[17];
  generate_date_time_format_start(log, datetime);

  fprintf(file, "%s\n", datetime);
}

static void
calendar_write_dtend(struct Log *log)
{
  fprintf(file, "DTEND;TZID=/freeassociation.sourceforge.net/America/Phoenix:");

  gchar datetime[17];
  generate_date_time_format_end(log, datetime);

  fprintf(file, "%s\n", datetime);
}

static void
calendar_write_summary(struct Log *log)
{
  fprintf(file, "SUMMARY:");
  fprintf(file, "Read - %s\n", active->title);
}

static void
calendar_write_sequence(struct Log *log)
{
  fprintf(file, "SEQUENCE:");
  fprintf(file, "%d\n", 0);
}

static void
calendar_write_description(struct Log *log)
{
  fprintf(file, "DESCRIPTION:");
  fprintf(file, "Page(s): %05d - %05d\n", log->start_pg, log->end_pg);
}

static void
calendar_write_location(struct Log *log)
{
  fprintf(file, "LOCATION:");
  fprintf(file, "Bookr\n");
}

static void
calendar_write_created(struct Log *log)
{
  fprintf(file, "CREATED:");

  gchar datetime[17];
  generate_date_time_format_end(log, datetime);

  fprintf(file, "%s\n", datetime);
}

static void
calendar_write_last_modified(struct Log *log)
{
  fprintf(file, "LAST-MODIFIED:");

  gchar datetime[17];
  generate_date_time_format_end(log, datetime);

  fprintf(file, "%s\n", datetime);
}
