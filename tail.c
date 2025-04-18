#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

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
} CircBuffer;

// size = lines
CircBuffer* cbuf_create(size_t size) {
  CircBuffer *buffer = malloc(sizeof(CircBuffer));

  if (buffer == NULL) {
    print_error("Memory allocation for '*buffer' failed");
    return NULL;
  }

  buffer->lines = malloc(LINE_LENGTH_LIMIT * size);

  if (buffer->lines == NULL) {
    print_error("Memory allocation for 'buffer->lines' failed");
    free(buffer);
    return NULL;
  }

  return buffer;
}

void cbuf_put(CircBuffer *buffer, const char *line) {

}

char* cbuf_get(CircBuffer *buffer) {

}

void cbuf_free(CircBuffer *buffer) {
  free(buffer->lines);
  free(buffer);
}

int main(const int argc, char *argv[]) {
  if (argc == 1) {
    
    char line[LINE_LENGTH_LIMIT];

    while (fgets(line, sizeof(line), stdin)) {
      printf("%s", line);
    }
  } else if (argc == 2) {
    FILE *file;
    const char *file_name = argv[1];
    file = fopen(file_name, "r");

    if (file == NULL) {
      print_error("File '%s' couldn't be opened", file_name);
      return 1;
    }

    char line[LINE_LENGTH_LIMIT];

    while (fgets(line, sizeof(line), file)) {
      printf("%s", line);
    }

    fclose(file);

  } else {
    print_error("Invalid number of arguments!");
    return 1;
  }
}
