#include "log.h"

static struct Book *active = NULL;

void
new_log(GtkButton *button,
        gpointer   data)
{
  active = get_book_active();

  if(active) {
    struct Log *new;
    new = create_log();

    insert_log(new);
  }

  hide_log_add(NULL, NULL);
}

struct Log *
create_log(void)
{
  struct Log *new;
  new = (struct Log *) malloc(sizeof(struct Log));

  GtkBuilder *builder;
  builder = get_log_add_builder();

  const gchar *data[9];
  guint day, month, year;

  GtkWidget *widget, *calendar;

  /* retrieve information */
  calendar = get_widget(builder, "bookr-log-add-calendar-calendar");
  gtk_calendar_get_date(GTK_CALENDAR(calendar), &year, &month, &day);

  widget = get_widget(builder, "bookr-log-add-time-entry-start-hour");
  data[0] = gtk_entry_get_text(GTK_ENTRY(widget));

  widget = get_widget(builder, "bookr-log-add-time-entry-start-minute");
  data[1] = gtk_entry_get_text(GTK_ENTRY(widget));

  widget = get_widget(builder, "bookr-log-add-time-button-start");
  data[2] = gtk_button_get_label(GTK_BUTTON(widget));

  widget = get_widget(builder, "bookr-log-add-time-entry-end-hour");
  data[3] = gtk_entry_get_text(GTK_ENTRY(widget));

  widget = get_widget(builder, "bookr-log-add-time-entry-end-minute");
  data[4] = gtk_entry_get_text(GTK_ENTRY(widget));

  widget = get_widget(builder, "bookr-log-add-time-button-end");
  data[5] = gtk_button_get_label(GTK_BUTTON(widget));

  widget = get_widget(builder, "bookr-log-add-pages-entry-start-page");
  data[6] = gtk_entry_get_text(GTK_ENTRY(widget));

  widget = get_widget(builder, "bookr-log-add-pages-entry-end-page");
  data[7] = gtk_entry_get_text(GTK_ENTRY(widget));

  printf("End Page: %s\n", data[7]);

  GObject *buffer;
  buffer = gtk_builder_get_object(GTK_BUILDER(builder),
                                  "bookr-log-add-notes-text-buffer");

  GtkTextIter start, end;
  gtk_text_buffer_get_start_iter(GTK_TEXT_BUFFER(buffer), &start);
  gtk_text_buffer_get_end_iter(GTK_TEXT_BUFFER(buffer), &end);

  data[8] = gtk_text_buffer_get_text(GTK_TEXT_BUFFER(buffer),
                                     &start, &end, FALSE);

  /* transfer information */
  new->day   = day;
  new->month = month;
  new->year  = year;

  new->start_hr  = atoi(data[0]);
  new->start_min = atoi(data[1]);
  new->end_hr    = atoi(data[3]);
  new->end_min   = atoi(data[4]);

  new->start_pg  = atoi(data[6]);
  new->end_pg    = atoi(data[7]);

  gint size;
  size = strlen(data[8]) + 1;

  new->note = (gchar *) malloc(sizeof(gchar) * size);
  strncpy(new->note, data[8], size);

  new->prev = NULL;
  new->next = NULL;
}

static void
insert_log(struct Log *new)
{
  if(!(active->log)) {
    active->log = new;
  }
  else {
    struct Log *iter;
    iter = active->log;

    while(iter->next) {
      iter = iter->next;
    }

    iter->next = new;
    new->prev  = iter;
  }
}

static void
print_log(struct Log *log)
{
  printf("Date: %02d/%02d/%02d\n", log->month, log->day, log->year);
  printf("Time: %02d:%02d - %02d:%02d\n", log->start_hr, log->start_min,
         log->end_hr, log->end_min);
  printf("Page: %05d to %05d\n", log->start_pg, log->end_pg);
  printf("Note:\n----------\n%s\n----------\n", log->note);

  printf("Prev: %p\n", log->prev);
  printf("Next: %p\n", log->next);
}
