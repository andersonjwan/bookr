#include "book-lexer.h"

static FILE *input = NULL;

void
init_book_lexer(FILE *file)
{
  input = file;
}

void
reset_book_lexer(void)
{
  input = NULL;
}

void
expect_key(gchar *expected)
{
  gchar *key;
  key = get_key();

  if(strcmp(key, expected) != 0) {
    g_printerr("SYNTAX ERROR!\n");

    g_printerr("Expected: %s\n", expected);
    g_printerr("Read: %s\n", key);
    exit(3);
  }

  free(key);
}

void
expect_value(gchar *expected, gchar *delimeter)
{
  gchar *value;
  value = get_value(delimeter);

  if(strcmp(value, expected) != 0) {
    g_printerr("SYNTAX ERROR!\n");

    g_printerr("Expected: %s\n", expected);
    g_printerr("Read: %s\n", value);
    exit(3);
  }
}

gchar *
get_key(void)
{
  gchar character;
  gint size = 64, index = 0;

  /* allocate initial buffer */
  gchar *buffer;
  buffer = (gchar *) malloc(sizeof(gchar) * size);

  /* test allocated pointer */
  if(buffer == NULL) {
    g_printerr("Memory Allocation Error: Insufficient Memory\n");
    exit(1);
  }

  /* read first character */
  character = getc(input);

  while(character != ':' && character != '\n' && character != EOF) {
    /* test index position */
    if(index >= size - 1) {
      /* buffer limit reached */
      size += 64;

      /* re-allocate more memory */
      buffer = realloc(buffer, size);

      if(buffer == NULL) {
        g_printerr("Memory Re-Allocation Error: Insufficient Memory\n");
        exit(2);
      }
    }

    /* append character to buffer */
    buffer[index] = character;
    ++index;

    /* read next character */
    character = getc(input);
  }

  /* append null-terminating character */
  buffer[index] = '\0';

  return buffer;
}

gchar *
get_value(gchar *delimeter)
{
  gchar character;
  gint size = 64, index = 0;

  /* allocate initial buffer */
  gchar *buffer;
  buffer = (gchar *) malloc(sizeof(gchar) * size);

  /* test allocated pointer */
  if(buffer == NULL) {
    g_printerr("Memory Allocation Error: Insufficient Memory\n");
    exit(1);
  }

  /* read first character */
  character = getc(input);

  while(character != '\n' && character != EOF
        && test_delimeter(character, delimeter)) {
    /* test index position */
    if(index >= size - 1) {
      /* buffer limit reached */
      size += 64;

      /* re-allocate more memory */
      buffer = realloc(buffer, size);

      if(buffer == NULL) {
        g_printerr("Memory Re-Allocation Error: Insufficient Memory\n");
        exit(2);
      }
    }

    /* append character to buffer */
    buffer[index] = character;
    ++index;

    /* read next character */
    character = getc(input);
  }

  /* append null-terminating character */
  buffer[index] = '\0';

  return buffer;
}

void
unget_key(gchar *key) {
  gint index;
  index = strlen(key) - 1;

  /* backtrack through string */
  while(index >= 0) {
    ungetc(key[index], input);
    --index;
  }
}

void
unget_value(gchar *value) {
  gint index;
  index = strlen(value) - 1;

  /* backtrack through string */
  while(index >= 0) {
    ungetc(value[index], input);
    --index;
  }
}

gchar *
peek_key(void)
{
  gchar character;
  gint size = 64, index = 0;

  /* allocate initial buffer */
  gchar *buffer;
  buffer = (gchar *) malloc(sizeof(gchar) * size);

  /* test allocated pointer */
  if(buffer == NULL) {
    g_printerr("Memory Allocation Error: Insufficient Memory\n");
    exit(1);
  }

  /* read first character */
  character = getc(input);

  while(character != ':' && character != '\n' && character != EOF) {
    /* test index position */
    if(index >= size - 1) {
      /* buffer limit reached */
      size += 64;

      /* re-allocate more memory */
      buffer = realloc(buffer, size);

      if(buffer == NULL) {
        g_printerr("Memory Re-Allocation Error: Insufficient Memory\n");
        exit(2);
      }
    }

    /* append character to buffer */
    buffer[index] = character;
    ++index;

    /* read next character */
    character = getc(input);
  }

  /* append null-terminating character */
  buffer[index] = '\0';

  ungetc(character, input);
  unget_key(buffer);

  return buffer;
}

gchar *
peek_value(void)
{
  gchar character;
  gint size = 64, index = 0;

  /* allocate initial buffer */
  gchar *buffer;
  buffer = (gchar *) malloc(sizeof(gchar) * size);

  /* test allocated pointer */
  if(buffer == NULL) {
    g_printerr("Memory Allocation Error: Insufficient Memory\n");
    exit(1);
  }

  /* read first character */
  character = getc(input);

  while(character != '\n' && character != EOF) {
    /* test index position */
    if(index >= size - 1) {
      /* buffer limit reached */
      size += 64;

      /* re-allocate more memory */
      buffer = realloc(buffer, size);

      if(buffer == NULL) {
        g_printerr("Memory Re-Allocation Error: Insufficient Memory\n");
        exit(2);
      }
    }

    /* append character to buffer */
    buffer[index] = character;
    ++index;

    /* read next character */
    character = getc(input);
  }

  /* append null-terminating character */
  buffer[index] = '\0';

  ungetc(character, input);
  unget_value(buffer);

  return buffer;
}

static gint
test_delimeter(gchar character, gchar *delimeter)
{
  if(delimeter == NULL) {
    return 1;
  }
  else {
    if(character != *delimeter) {
      return 1;
    }
    else {
      return 0;
    }
  }
}
