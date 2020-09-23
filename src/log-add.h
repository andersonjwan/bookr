#ifndef LOG_ADD_H
#define LOG_ADD_H

#include "builder.h"

/* forward declarations */
GtkBuilder * get_log_add_builder(void);
void show_log_add(void);
void hide_log_add(GtkButton *, gpointer);

static void clear_log_add(void);

#endif
