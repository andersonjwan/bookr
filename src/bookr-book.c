#include "bookr-book.h"

static struct Book *active = NULL;

struct Book *
get_book_active(void)
{
  return active;
}

void
new_book(GtkButton *button,
         gpointer   data)
{
  if(active) {
    save_book_file();
    free_book();
  }

  active = create_book(GTK_WIDGET(data));

  update_book_list(active->title, active->path);
  hide_book_add(NULL, NULL);

  create_book_file();
  save_book_file();

  select_book(NULL, active->path);
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
  new->isbn = (gchar *) malloc(sizeof(gchar) * size);
  strncpy(new->isbn, data[6], size);

  size = strlen(data[9]) + 1;
  new->cover = (gchar *) malloc(sizeof(gchar) * size);
  strncpy(new->cover, data[9], size);

  size = strlen(data[10]) + 1;
  new->calendar = (gchar *) malloc(sizeof(gchar) * size);
  strncpy(new->calendar, data[10], size);

  new->log = NULL;
  new->path = create_book_path(new->isbn, new->title);

  return new;
}

static void
create_book_file(void)
{
  gchar *path;
  path = create_book_path(active->isbn, active->title);

  /* create file */
  FILE *file;
  file = fopen(path, "w");

  if(!file) {
    g_printerr("Error %d: Unable to open file: %s\n", 1, path);
    exit(1);
  }

  fclose(file);
}

void
select_book(GtkModelButton *button,
            gpointer        data)
{
  gchar *path;
  path = (gchar *) data;

  if(active) {
    save_book_file();
    free_book();
  }

  active = select_book_file(path);

  update_stacks(active);
  print_book();
}

static struct Book *
select_book_file(gchar *path)
{
  struct Book *book;

  FILE *file;
  file = fopen(path, "r");

  if(!file) {
    g_printerr("Error %d: Unable to open file: %s\n", 1, path);
    exit(1);
  }

  book = parse_book_file(file);
  fclose(file);

  return book;
}

static void
free_book(void)
{
  /* free allocated memory */
  g_free((gchar *) active->title);
  g_free((gchar *) active->author);
  g_free((gchar *) active->publisher);
  g_free((gchar *) active->language);
  g_free((gchar *) active->isbn);
  g_free((gchar *) active->cover);
  g_free((gchar *) active->calendar);

  /* free logs */
  if(active->log) {
    free_log(active->log);
  }

  g_free((struct Book *) active);
  active = NULL;
  return;
}

gchar *
create_book_path(gchar *isbn, gchar *title)
{
  gchar *prefix, *subpath;
  prefix  = getenv("HOME");
  subpath = "/.local/share/bookr/data/";

  gchar filename[strlen(isbn) + strlen(title) + 10];
  sprintf(filename, "[%s] - %s.dat", isbn, title);

  /* build path */
  gint size;
  size = strlen(prefix) + strlen(subpath) + strlen(filename) + 1;

  gchar *path;
  path = (gchar *) malloc(sizeof(gchar) * size);

  strcpy(path, prefix);
  strcat(path, subpath);
  strcat(path, filename);

  return path;
}

static void
print_book(void)
{
  if(active) {
    printf("Title: %s\n", active->title);
    printf("Author: %s\n", active->author);
    printf("Publisher: %s\n", active->publisher);
    printf("Language: %s\n", active->language);
    printf("ISBN: %s\n", active->isbn);
    printf("Published: %d\n", active->published);
    printf("Edition: %d\n", active->edition);
    printf("Start: %d\n", active->start);
    printf("Length: %d\n", active->pages);

    printf("Cover: %s\n", active->cover);
    printf("Calendar: %s\n", active->calendar);
    printf("Log: %p\n", active->log);
    printf("Path: %s\n", active->path);
  }

  return;
}
