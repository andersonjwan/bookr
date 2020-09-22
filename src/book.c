#include "book.h"

static struct Book *active = NULL;

void
new_book(GtkButton *button,
         gpointer   data)
{
  if(!active) {
    /* first book */
    active = create_book(GTK_WIDGET(data));
  }
  else {
    free_book();
    active = create_book(GTK_WIDGET(data));
  }

  update_book_list(active->title);

  hide_book_add(NULL, NULL);
  create_book_file();
  print_book();
}

static struct Book *
create_book(GtkWidget *container)
{
  struct Book *new;
  new = (struct Book *) malloc(sizeof(struct Book));

  int i = 0;
  const gchar *data[11];
  GtkEntry    *entry;

  GList *child;
  child = gtk_container_get_children(GTK_CONTAINER(container));

  /* retrieve information */
  while(child) {
    entry = GTK_ENTRY(child->data);
    data[i] = gtk_entry_get_text(GTK_ENTRY(entry));

    /* next entry */
    child = child->next;
    ++i;
  }

  /* numerical data */
  new->published = atoi(data[3]);
  new->edition   = atoi(data[4]);
  new->start     = atoi(data[7]);
  new->pages     = atoi(data[8]);

  /* allocated data */
  gint size;

  size = strlen(data[0]) + 1;
  new->title = (gchar *) malloc(sizeof(gchar) * size);
  strncpy(new->title, data[0], size);

  size = strlen(data[1]) + 1;
  new->author = (gchar *) malloc(sizeof(gchar) * size);
  strncpy(new->author, data[1], size);

  size = strlen(data[2]) + 1;
  new->publisher = (gchar *) malloc(sizeof(gchar) * size);
  strncpy(new->publisher, data[2], size);

  size = strlen(data[5]) + 1;
  new->language = (gchar *) malloc(sizeof(gchar) * size);
  strncpy(new->language, data[5], size);

  size = strlen(data[6]) + 1;
  new->ISBN = (gchar *) malloc(sizeof(gchar) * size);
  strncpy(new->ISBN, data[6], size);

  size = strlen(data[9]) + 1;
  new->cover = (gchar *) malloc(sizeof(gchar) * size);
  strncpy(new->cover, data[9], size);

  size = strlen(data[10]) + 1;
  new->calendar = (gchar *) malloc(sizeof(gchar) * size);
  strncpy(new->calendar, data[10], size);

  new->log = NULL;

  return new;
}

static void
free_book(void)
{
  /* free allocated memory */
  g_free((gchar *) active->title);
  g_free((gchar *) active->author);
  g_free((gchar *) active->publisher);
  g_free((gchar *) active->language);
  g_free((gchar *) active->ISBN);
  g_free((gchar *) active->cover);
  g_free((gchar *) active->calendar);

  /* free logs */
  if(active->log) {
    // TODO
  }

  g_free((struct Book *) active);
  active = NULL;
  return;
}

static void
create_book_file(void)
{
  /* create file name */
  gchar *prefix = getenv("HOME");
  gchar *title  = active->title;

  gint size;
  size = strlen(prefix) + strlen(title) + 1;

  gchar path[size];
  strcpy(path, prefix);

  gchar name[(38 + strlen(title))];
  snprintf(name, (strlen(title) + 38),
           "/.local/share/bookr/data/Book - %s.data", title);
  strncat(path, name, strlen(name));

  printf("Path: %s\n", path);
  /* create file */
  FILE *file;
  file = fopen(path, "w");

  fclose(file);
}

void
select_book(GtkModelButton *button,
            gpointer        data)
{
  gchar *title;
  title = (gchar *) data;

  select_book_file(title);
}

static void
select_book_file(gchar *title)
{
  /* create path */
  gchar *prefix = getenv("HOME");

  gint size;
  size = strlen(prefix) + strlen(title) + 1;

  gchar path[size];
  strcpy(path, prefix);

  gchar name[(38 + strlen(title))];
  snprintf(name, (strlen(title) + 38),
           "/.local/share/bookr/data/Book - %s.data", title);

  strncat(path, name, strlen(name));

  printf("Path: %s\n", path);

  FILE *file;
  file = fopen(path, "r");

  if(!file) {
    fprintf(stderr, "Unable to open\n");
  }
  fclose(file);
}

static void
print_book(void)
{
  if(active) {
    printf("Title: %s\n", active->title);
    printf("Author: %s\n", active->author);
    printf("Publisher: %s\n", active->publisher);
    printf("Language: %s\n", active->language);
    printf("ISBN: %s\n", active->ISBN);
    printf("Published: %d\n", active->published);
    printf("Edition: %d\n", active->edition);
    printf("Start: %d\n", active->start);
    printf("Length: %d\n", active->pages);

    printf("Cover: %s\n", active->cover);
    printf("Calendar: %s\n", active->calendar);
    printf("Log: %p\n", active->log);
  }

  return;
}
