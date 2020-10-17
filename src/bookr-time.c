#include "bookr-time.h"

guint
convert_time(guint hour, const gchar *label)
{
  switch(hour) {
  case 12: {
    if(strcmp(label, "AM") == 0)
      return 0;
    else
      return 12;
  }
    break;
  default: {
    if(strcmp(label, "AM") == 0)
      return hour;
    else
      return hour + 12;
  }
    break;
  }
}

void
convert_time_format(gchar *format_str, guint hour, guint minute)
{
  switch(hour) {
  case 0:
    hour = 12;
    sprintf(format_str, "%02d:%02d AM", hour, minute);
    break;
  default: {
    if(hour > 12) {
      sprintf(format_str, "%02d:%02d PM", hour - 12, minute);
    }
    else if(hour == 12){
      sprintf(format_str, "%02d:%02d AM", hour, minute);
    }
    else {
      sprintf(format_str, "%02d:%02d PM", hour, minute);
    }
  }
  }
}

void
get_current_date(guint *day, guint *month, guint *year)
{
  time_t rawtime;
  struct tm *timeinfo;

  time(&rawtime);
  timeinfo = localtime(&rawtime);

  *day   = timeinfo->tm_mday;
  *month = timeinfo->tm_mon;
  *year  = timeinfo->tm_year + 1900;
}

void
generate_date_time_format_start(struct Log *log, gchar *result)
{
  sprintf(result, "%04d%02d%02dT%02d%02d00",
          log->year, log->month, log->day, log->start_hr, log->start_min);
}

void generate_date_time_format_end(struct Log *log, gchar *result)
{
  sprintf(result, "%04d%02d%02dT%02d%02d00",
          log->year, log->month, log->day, log->end_hr, log->end_min);
}
