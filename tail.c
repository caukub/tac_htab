#include <stdio.h>

#include <stdlib.h>

#include <stdarg.h>

#include <stdbool.h>

#include <string.h>

#include <assert.h>

void print_error(const char * fmt, ...) {
  va_list args;

  fprintf(stderr, "Error: ");

  va_start(args, fmt);

  vfprintf(stderr, fmt, args);

  va_end(args);
}

#define LINE_LENGTH_LIMIT 4096

typedef struct {
  char ** lines;
  size_t size;
  size_t read_idx;
  size_t write_idx;
  bool is_full;
}
CircBuffer;

CircBuffer* cbuf_create(size_t size) {
  assert(size > 0);
  CircBuffer *buffer = malloc(sizeof(CircBuffer));

  if (buffer == NULL) {
    print_error("Memory allocation for '*buffer' failed");
    return NULL;
  }

  buffer->read_idx = 0;
  buffer->write_idx = 0;
  buffer->size = size;
  buffer->is_full = false;

  buffer->lines = malloc(sizeof(char*) * size);

  if (buffer->lines == NULL) {
    print_error("Memory allocation for 'buffer->lines' failed");
    free(buffer);
    return NULL;
  }

  return buffer;
}

void cbuf_put(CircBuffer * buffer, const char * line) {
  if (buffer->lines[buffer->write_idx] != NULL) {
    free(buffer->lines[buffer->write_idx]);
  }

  buffer->lines[buffer->write_idx] = strdup(line);
  if (!buffer->lines[buffer->write_idx]) {
    print_error("Chyba při alokaci paměti pro řádek");
    return;
  }

  if (buffer->is_full) {
    buffer->read_idx = (buffer->read_idx + 1) % buffer->size;
  }

  buffer->write_idx = (buffer->write_idx + 1) % buffer->size;

  if (buffer->write_idx == buffer->read_idx) {
    buffer->is_full = 1;
  }
}

void cbuf_free(CircBuffer * buffer) {
  free(buffer->lines);
  free(buffer);
}

char* cbuf_get(CircBuffer * buffer, int index) {
  if (buffer->read_idx == buffer->write_idx && !buffer->is_full) {
    return NULL;
  }

  size_t count = buffer->is_full ? buffer->size : buffer->write_idx - buffer->read_idx;

  if (count < 0) {
    count += buffer->size;
  }

  if (index < 0 || index >= count) {
    return NULL;
  }

  size_t real_idx = (buffer->read_idx + index) % buffer->size;

  return buffer->lines[real_idx];
}

size_t get_line_count(CircBuffer * buffer) {
  if (buffer->read_idx == buffer->write_idx) {
    return buffer->is_full ? buffer->size : 0;
  }

  if (buffer->write_idx > buffer->read_idx) {
    return buffer->write_idx - buffer->read_idx;
  } else {
    return buffer->size - buffer->read_idx + buffer->write_idx;
  }
}

int main(const int argc, char *argv[]) {
  char line[LINE_LENGTH_LIMIT];

  size_t lines_to_print = 0;

  if (true) {
    lines_to_print = 0;
  } else {
    lines_to_print = 0;
  }

  if (lines_to_print == 0) {
    return 0;
  }

  CircBuffer *buffer = cbuf_create(lines_to_print);

  if (buffer == NULL) {
    print_error("Buffer '*buffer' couldn't be allocated");
  }

  if (argc == 1) {
    while (fgets(line, sizeof(line), stdin)) {
      cbuf_put(buffer, line);
    }
  } else if (argc == 2) {
    FILE *file;
    const char *file_name = argv[1];
    file = fopen(file_name, "r");

    if (file == NULL) {
      print_error("File '%s' couldn't be opened", file_name);
      return 1;
    }

    while (fgets(line, sizeof(line), file)) {
      cbuf_put(buffer, line);
    }

    fclose(file);

  } else {
    print_error("Invalid number of arguments!");
    return 1;
  }

  size_t line_count = get_line_count(buffer);

  for (size_t idx = 0; idx < line_count; ++idx) {
    char *current_line = cbuf_get(buffer, idx);
    if (current_line) {
      printf("%s", current_line);
    }
  }

  cbuf_free(buffer);
}