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
