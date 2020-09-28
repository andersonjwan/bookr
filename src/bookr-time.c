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
