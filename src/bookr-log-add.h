#ifndef BOOKR_LOG_ADD_H
#define BOOKR_LOG_ADD_H

#include "bookr-builder.h"
#include "bookr-stats.h"

/* forward declarations */
GtkBuilder * get_log_add_builder(void);
void show_log_add(void);
void hide_log_add(GtkButton *, gpointer);

void clear_log_add(void);

static void autofill_log_add(void);
static void autofill_log_add_calendar(void);
static void autofill_log_add_start_page(void);

void format_log_add_time_hour(GtkEntry *, gpointer);
void format_log_add_time_minute(GtkEntry *, gpointer);
#endif
