#include "bookr-stack.h"

static GtkBuilder *builder;
static GdkPixbuf  *pxbuf = NULL;

void
update_stacks(struct Book *book)
{
  if(!builder) {
    builder = get_builder_builder();
  }

  update_log_stack(book);
  update_book_stack(book);
}

static void
update_log_stack(struct Book *book)
{
  update_log_stack_header(book);
  update_log_stack_progress(book);
}

static void
update_log_stack_header(struct Book *book)
{
  GtkWidget *label;

  /* update title label */
  label = get_widget(builder,"bookr-main-stack-logs-header-label-title");
  gtk_label_set_text(GTK_LABEL(label), book->title);

  /* update author label */
  label = get_widget(builder, "bookr-main-stack-logs-header-label-authors");
  gtk_label_set_text(GTK_LABEL(label), book->author);
}

static void
update_log_stack_progress(struct Book *book)
{
  GtkWidget *bar;
  bar = get_widget(builder, "bookr-main-stack-logs-progress");

  gdouble progress;
  progress = bookr_stats_get_progress(book);

  gtk_progress_bar_set_fraction(GTK_PROGRESS_BAR(bar), progress);

  gchar percent[4];
  sprintf(percent, "%d%%", (gint) (progress * 100));
  gtk_widget_set_tooltip_text(GTK_WIDGET(bar), percent);
}

static void
update_book_stack(struct Book *book)
{
  update_book_stack_information(book);
  update_book_stack_log_list(book);

  GtkWidget *paned;
  paned = get_widget(builder, "bookr-main-stack-books-pane-info");

  if(!book->log)
    gtk_paned_set_position(GTK_PANED(paned), 0);
  else
    gtk_paned_set_position(GTK_PANED(paned), 250);
}

static void
update_book_stack_information(struct Book *book)
{
  update_book_stack_information_cover(book);
  update_book_stack_information_header(book);
  update_book_stack_information_attributes(book);
}

static void
update_book_stack_information_cover(struct Book *book)
{
  GtkWidget *image;
  image = get_widget(builder, "bookr-main-stack-books-info-cover-image");

  if(pxbuf) {
    g_object_unref(G_OBJECT(pxbuf));
  }

  GError    *error = NULL;
  pxbuf = gdk_pixbuf_new_from_file_at_size(book->cover,
                                           -1, 480, &error);

  gtk_image_set_from_pixbuf(GTK_IMAGE(image), GDK_PIXBUF(pxbuf));
}

static void
update_book_stack_information_header(struct Book *book)
{
  GtkWidget *widget;
  widget = get_widget(builder,
                      "bookr-main-stack-books-info-details-header-title-label");
  gtk_label_set_text(GTK_LABEL(widget), book->title);

  widget = get_widget(builder,
                      "bookr-main-stack-books-info-details-header-author-label");
  gtk_label_set_text(GTK_LABEL(widget), book->author);
}

static void
update_book_stack_information_attributes(struct Book *book)
{
  GtkWidget *label;

  label = get_widget(builder,
                     "bookr-main-stack-books-info-details-attributes-title-label-content");
  gtk_label_set_text(GTK_LABEL(label), book->title);

  label = get_widget(builder,
                     "bookr-main-stack-books-info-details-attributes-author-label-content");
  gtk_label_set_text(GTK_LABEL(label), book->author);

  label = get_widget(builder,
                     "bookr-main-stack-books-info-details-attributes-publisher-label-content");
  gtk_label_set_text(GTK_LABEL(label), book->publisher);

  gchar data[5];
  sprintf(data, "%04d", book->published);
  label = get_widget(builder,
                     "bookr-main-stack-books-info-details-attributes-published-label-content");
  gtk_label_set_text(GTK_LABEL(label), data);

  sprintf(data, "%d", book->edition);
  label = get_widget(builder,
                     "bookr-main-stack-books-info-details-attributes-edition-label-content");
  gtk_label_set_text(GTK_LABEL(label), data);

  label = get_widget(builder,
                     "bookr-main-stack-books-info-details-attributes-language-label-content");
  gtk_label_set_text(GTK_LABEL(label), book->language);

  label = get_widget(builder,
                     "bookr-main-stack-books-info-details-attributes-isbn-label-content");
  gtk_label_set_text(GTK_LABEL(label), book->isbn);

  gchar start[10];
  sprintf(start, "%d", book->start);
  label = get_widget(builder,
                     "bookr-main-stack-books-info-details-attributes-start-label-content");
  gtk_label_set_text(GTK_LABEL(label), start);

  gchar length[10];
  sprintf(length, "%d", book->pages);
  label = get_widget(builder,
                     "bookr-main-stack-books-info-details-attributes-print-label-content");
  gtk_label_set_text(GTK_LABEL(label), length);
}

static void
update_book_stack_log_list(struct Book *book)
{
  GtkWidget *list;
  list = get_widget(builder,
                    "bookr-main-stack-books-scrolled-viewport-list-box");

  update_book_stack_log_list_clear(list);
  update_book_stack_log_list_build(list, book);

  gtk_widget_show_all(GTK_WIDGET(list));
}

static void
update_book_stack_log_list_clear(GtkWidget *list)
{
  GList *child, *iter;
  child = gtk_container_get_children(GTK_CONTAINER(list));
  iter = child;

  while(iter) {
    gtk_widget_destroy(GTK_WIDGET(iter->data));
    iter = iter->next;
  }

  g_list_free(g_steal_pointer(&child));
}

static void
update_book_stack_log_list_build(GtkWidget *list, struct Book *book)
{
  struct Log *iter;
  iter = book->log;

  GtkWidget *child;

  while(iter) {
    child = update_book_stack_log_list_build_item(book, iter);
    gtk_list_box_prepend(GTK_LIST_BOX(list), GTK_WIDGET(child));

    iter = iter->next;
  }
}

static GtkWidget *
update_book_stack_log_list_build_item(struct Book *book, struct Log *log)
{
  GtkWidget *item;
  item = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
  GtkWidget *box;
  box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
  gtk_container_set_border_width(GTK_CONTAINER(box), 5);

  GtkWidget *header, *content;
  header  = update_book_stack_log_list_build_item_header(book, log);
  content = update_book_stack_log_list_build_item_content(log);

  gtk_box_pack_start(GTK_BOX(box), GTK_WIDGET(header),
                     FALSE, FALSE, 0);
  gtk_box_pack_start(GTK_BOX(box), GTK_WIDGET(content),
                     FALSE, FALSE, 0);

  gtk_box_pack_start(GTK_BOX(item), GTK_WIDGET(box),
                     FALSE, FALSE, 0);

  GtkWidget *separator;
  separator = gtk_separator_new(GTK_ORIENTATION_HORIZONTAL);

  gtk_box_pack_end(GTK_BOX(item), GTK_WIDGET(separator),
                   FALSE, FALSE, 0);

  update_book_stack_log_list_build_item_tooltip(item, log);

  return item;
}

static GtkWidget *
update_book_stack_log_list_build_item_header(struct Book *book, struct Log *log)
{
  GtkWidget *box;
  box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);

  GtkWidget *label_01, *label_02, *label_03;

  gchar data_01[strlen("Book Log Entry") + 1];
  sprintf(data_01, "Book Log Entry");
  label_01 = gtk_label_new(data_01);

  /* attributes */
  PangoAttrList *log_attr, *mod_attr;
  log_attr = pango_attr_list_new();

  PangoAttribute *log_01;
  log_01 = pango_attr_weight_new(PANGO_WEIGHT_SEMIBOLD);
  pango_attr_list_insert(log_attr, log_01);

  /* apply attributes */
  // gtk_label_set_attributes(GTK_LABEL(label_01), log_attr);

  pango_attr_list_unref(log_attr);

  gtk_box_pack_start(GTK_BOX(box), GTK_WIDGET(label_01),
                     FALSE, FALSE, 0);

  return box;
}

static GtkWidget *
update_book_stack_log_list_build_item_content(struct Log *log)
{
  GtkWidget *box;
  box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);

  GtkWidget *label;

  gchar content[strlen("##/##/####, ##### - #####") + 1];
  sprintf(content, "%02d/%02d/%04d, %05d - %05d", log->month, log->day,
          log->year, log->start_pg, log->end_pg);
  label = gtk_label_new(content);

  PangoAttrList *content_attr;
  content_attr = pango_attr_list_new();

  PangoAttribute *attr_01, *attr_02;
  attr_01 = pango_attr_scale_new(0.75);
  attr_02 = pango_attr_style_new(PANGO_STYLE_ITALIC);

  pango_attr_list_insert(content_attr, attr_01);
  pango_attr_list_insert(content_attr, attr_02);

  gtk_label_set_attributes(GTK_LABEL(label), content_attr);

  pango_attr_list_unref(content_attr);

  gtk_box_pack_start(GTK_BOX(box), GTK_WIDGET(label),
                     FALSE, FALSE, 0);

  return box;
}

static void
update_book_stack_log_list_build_item_tooltip(GtkWidget *box, struct Log *log)
{
  gchar *tooltip;
  gint size;

  size = strlen("<b>Log ######</b>\n\n") + 1;
  tooltip = (gchar *) malloc(sizeof(gchar) * size);

  size += strlen("Date: ##/##/####\n");
  size += strlen("Time: ##:## - ##:##\n");
  size += strlen("Pages: ##### - #####\n");
  size += strlen("Note: ") + strlen(log->note);

  tooltip = realloc(tooltip, size);

  sprintf(tooltip, "<b>Log #%d</b>\n\n", log->number);

  gchar date[strlen("Date: ##/##/####\n") + 1];
  sprintf(date, "Date: %02d/%02d/%04d\n", log->month, log->day, log->year);
  strcat(tooltip, date);

  gchar time[strlen("Time: ##:## - ##:##\n") + 1];
  sprintf(time, "Time: %02d:%02d - %02d:%02d\n", log->start_hr, log->start_min,
          log->end_hr, log->end_min);
  strcat(tooltip, time);
  gchar pages[strlen("Pages: ##### - #####\n") + 1];
  sprintf(pages, "Pages: %05d - %05d\n", log->start_pg, log->end_pg);
  strcat(tooltip, pages);

  gchar note[strlen("Note: \n") + strlen(log->note) + 1];
  sprintf(note, "Note: %s", log->note);
  strcat(tooltip, note);

  gtk_widget_set_tooltip_markup(GTK_WIDGET(box), tooltip);

  g_free(tooltip);
}
