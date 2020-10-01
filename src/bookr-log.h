#ifndef BOOKR_LOG_H
#define BOOKR_LOG_H

#include "bookr-main.h"
#include "bookr-time.h"

struct Log {
  /* date */
  guint day;             // log day
  guint month;           // log month
  guint year;            // log year

  /* times */
  gint start_hr;        // log's start hour
  gint start_min;       // log's start minute
  gint end_hr;          // log's end hour
  gint end_min;         // log's end minute

  /* pages */
  guint start_pg;       // log's start page
  guint end_pg;         // log's end page

  gchar *note;          // log's note

  /* log information */
  guint number;
  guint calendar;

  struct Log *prev;     // previous log
  struct Log *next;     // next log
};

/* forward declarations */
void new_log(GtkButton *, gpointer);
static struct Log * create_log(void);
static void insert_log(struct Log *);

void free_log(struct Log *);

static void print_log(struct Log *);

void swap_format(GtkButton *, gpointer);
static void check_swap(GtkButton *);

void generate_log_uid(struct Log *, gchar *);
#endif
