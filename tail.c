// tail.c
// Řešení IJC-DU2, část A, 25. 4. 2025
// Autor: Jakub Trumpeš (xtrumpj00), FIT
// Přeloženo: gcc version 11.5.0 (GCC)

#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>
#include <assert.h>

void print_error(const char *fmt, ...) {
  va_list args;

  fprintf(stderr, "Error: ");

  va_start(args, fmt);

  vfprintf(stderr, fmt, args);

  va_end(args);
}

#define LINE_LENGTH_LIMIT 4096

typedef struct {
  char **lines;
  size_t size;
  size_t read_idx;
  size_t write_idx;
  bool is_full;
} CircBuffer;

CircBuffer* cbuf_create(size_t size) {
  assert(size > 0);

  CircBuffer *buffer = malloc(sizeof(CircBuffer));

  if (buffer == NULL) {
    print_error("Memory allocation for '*buffer' failed\n");
    return NULL;
  }

  buffer->read_idx = 0;
  buffer->write_idx = 0;
  buffer->size = size;
  buffer->is_full = false;

  buffer->lines = malloc(sizeof(char*) * size);

  if (buffer->lines == NULL) {
    print_error("Memory allocation for 'buffer->lines' failed\n");
    free(buffer);
    return NULL;
  }

  return buffer;
}

void cbuf_put(CircBuffer *buffer, const char *line) {
  if (buffer->lines[buffer->write_idx] != NULL) {
    free(buffer->lines[buffer->write_idx]);
  }

  buffer->lines[buffer->write_idx] = strdup(line);

  if (!buffer->lines[buffer->write_idx]) {
    print_error("Error occured while allocating memory for new line\n");
    if (buffer->lines[buffer->write_idx] != NULL) {
      free(buffer->lines[buffer->write_idx]);
    }
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

void cbuf_free(CircBuffer *buffer) {
  if (buffer->lines) {
    for (size_t idx = 0; idx < buffer->size; ++idx) {
      free(buffer->lines[idx]);
    }
    free(buffer->lines);
  }

  free(buffer);
}

char* cbuf_get(CircBuffer *buffer, int index) {
  if (buffer->read_idx == buffer->write_idx && !buffer->is_full) {
    return NULL;
  }

  size_t count = buffer->is_full ? buffer->size : buffer->write_idx - buffer->read_idx;

  if (index < 0 || (size_t) index >= count) {
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

void read_stdin(CircBuffer *buffer, char *line) {
  bool line_limit_reached = false;
  
  while (fgets(line, LINE_LENGTH_LIMIT, stdin)) {
    size_t length = strlen(line);
    
    if (length == LINE_LENGTH_LIMIT - 1 && line[length - 1] != '\n') {
      if (!line_limit_reached) {
        print_error("Maximum line length (%d chars) exceeded, remaining of the line is not printed\n", LINE_LENGTH_LIMIT - 1);
        line_limit_reached = true;
      }

      int ch;
      
      while ((ch = fgetc(stdin)) != '\n' && ch != EOF);
    }

    cbuf_put(buffer, line);
  }
}

void read_file(CircBuffer *buffer, char *line, const char *file_name) {
  FILE *file = fopen(file_name, "r");
  
  if (file == NULL) {
    print_error("File '%s' couldn't be opened\n", file_name);
    cbuf_free(buffer);
    exit(1);
  }
  
  bool line_limit_reached = false;
  
  while (fgets(line, LINE_LENGTH_LIMIT, file)) {
    size_t length = strlen(line);

    if (length == LINE_LENGTH_LIMIT - 1 && line[length - 1] != '\n') {
      if (!line_limit_reached) {
        print_error("A line exceeded the maximum allowed length (%d chars), remaining of the line is not printed\n", LINE_LENGTH_LIMIT - 1);
        line_limit_reached = true;
      }

      int ch;
      while ((ch = fgetc(file)) != '\n' && ch != EOF);
    }

    cbuf_put(buffer, line);
    
    }
    
    fclose(file);
}

int main(const int argc, char *argv[]) {
  int opt;

  int lines_to_print = 10;

  while ((opt = getopt(argc, argv, "n:")) != -1) {
    switch(opt) {
      case 'n': {
        char *endptr;

        lines_to_print = strtol(optarg, &endptr, 10);

        if (*endptr != '\0') {
          print_error("Value of -n is not a valid number\n");
          exit(1);
        }

        break;
      }
      case '?':
        print_error("Invalid switch has been provided\n");
        exit(1);
        break;
    }
  }

  char *file_name = NULL;

  if (argv[optind] != NULL) {
    file_name = argv[optind];
  }

  if (lines_to_print == 0) {
    return 0;
  } else if (lines_to_print < 0) {
    print_error("The number of lines to print cannot be negative\n");
    return 1;
  }

  CircBuffer *buffer = cbuf_create((size_t) lines_to_print);

  if (buffer == NULL) {
    print_error("Buffer '*buffer' allocation failed\n");
    return 1;
  }

  char line[LINE_LENGTH_LIMIT];

  if (file_name == NULL) {
    read_stdin(buffer, line);
  } else {
    read_file(buffer, line, file_name);
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
