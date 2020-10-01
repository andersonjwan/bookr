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
update_book_stack(struct Book *book)
{
  update_book_stack_information(book);
  update_book_stack_log_list(book);
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
                                           320, -1, &error);

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

  label = get_widget(builder, "bookr-main-stack-books-info-details-attributes-title-label-content");
  gtk_label_set_text(GTK_LABEL(label), book->title);

  label = get_widget(builder, "bookr-main-stack-books-info-details-attributes-author-label-content");
  gtk_label_set_text(GTK_LABEL(label), book->author);

  label = get_widget(builder, "bookr-main-stack-books-info-details-attributes-publisher-label-content");
  gtk_label_set_text(GTK_LABEL(label), book->publisher);

  gchar data[5];
  sprintf(data, "%04d", book->published);
  label = get_widget(builder, "bookr-main-stack-books-info-details-attributes-published-label-content");
  gtk_label_set_text(GTK_LABEL(label), data);

  sprintf(data, "%d", book->edition);
  label = get_widget(builder, "bookr-main-stack-books-info-details-attributes-edition-label-content");
  gtk_label_set_text(GTK_LABEL(label), data);

  label = get_widget(builder, "bookr-main-stack-books-info-details-attributes-language-label-content");
  gtk_label_set_text(GTK_LABEL(label), book->language);

  label = get_widget(builder, "bookr-main-stack-books-info-details-attributes-isbn-label-content");
  gtk_label_set_text(GTK_LABEL(label), book->isbn);

  gchar start[10];
  sprintf(start, "%d", book->start);
  label = get_widget(builder, "bookr-main-stack-books-info-details-attributes-start-label-content");
  gtk_label_set_text(GTK_LABEL(label), start);

  gchar length[10];
  sprintf(length, "%d", book->pages);
  label = get_widget(builder, "bookr-main-stack-books-info-details-attributes-print-label-content");
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
  GtkWidget *child;
  child = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
  gtk_container_set_border_width(GTK_CONTAINER(child), 10);

  GtkWidget *header_box, *data_box;
  header_box = update_book_stack_log_list_build_item_header(log);
  data_box   = update_book_stack_log_list_build_item_data(book, log);

  gtk_box_pack_start(GTK_BOX(child), GTK_WIDGET(header_box),
                     FALSE, FALSE, 0);
  gtk_box_pack_start(GTK_BOX(child), GTK_WIDGET(data_box),
                     FALSE, FALSE, 0);

  return child;
}

static GtkWidget *
update_book_stack_log_list_build_item_header(struct Log *log)
{
  GtkWidget *box;
  box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);

  GtkWidget *label_01, *label_02;

  gchar data_01[strlen("Log No. #####") + 1];
  sprintf(data_01, "Log No. %05d", log->number);
  label_01 = gtk_label_new(data_01);

  gchar data_02[strlen("##/##/####") + 1];
  sprintf(data_02, "%02d/%02d/%04d", log->month, log->day, log->year);
  label_02 = gtk_label_new(data_02);

  /* attributes */
  PangoAttrList *attributes;
  attributes = pango_attr_list_new();

  PangoAttribute *attr_01, *attr_02, *attr_03;
  attr_01 = pango_attr_style_new(PANGO_STYLE_ITALIC);
  attr_02 = pango_attr_scale_new(0.75);
  attr_03 = pango_attr_foreground_new(186 * 257, 189 * 257, 182 * 257);

  pango_attr_list_insert(attributes, attr_01);
  pango_attr_list_insert(attributes, attr_02);
  pango_attr_list_insert(attributes, attr_03);

  /* apply attributes */
  gtk_label_set_attributes(GTK_LABEL(label_01), attributes);
  gtk_label_set_attributes(GTK_LABEL(label_02), attributes);

  //pango_attribute_destroy(attr_01);
  //pango_attribute_destroy(attr_02);
  //pango_attribute_destroy(attr_03);

  //pango_attr_list_unref(attributes);

  gtk_box_pack_start(GTK_BOX(box), GTK_WIDGET(label_01),
                     FALSE, FALSE, 0);
  gtk_box_pack_end(GTK_BOX(box), GTK_WIDGET(label_02),
                   FALSE, FALSE, 0);

  return box;
}

static GtkWidget *
update_book_stack_log_list_build_item_data(struct Book *book, struct Log *log)
{
  GtkWidget *box;
  box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);

  return box;
}
