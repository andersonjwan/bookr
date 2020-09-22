#ifndef LOG_H
#define LOG_H

#include "main.h"

struct Log {
  /* date */
  gint day;             // log day
  gint month;           // log month
  gint year;            // log year

  /* times */
  gint start_hr;        // log's start hour
  gint start_min;       // log's start minute
  gint end_hr;          // log's end hour
  gint end_min;         // log's end minute

  /* pages */
  guint start_pg;       // log's start page
  guint end_pg;         // log's end page

  struct Log *prev;     // previous log
  struct Log *next;     // next log
};

#endif
