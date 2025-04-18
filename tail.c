#include <stdio.h>
#include <stdlib.h>

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
  buffer->lines = malloc(LINE_LENGTH_LIMIT * size);

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

    while (fgets(line, sizeof(line), stdio)) {
      printf("%s", line);
    }
  } else if (argc == 2) {
    FILE *file;
    const char *file_name = argv[1];
    file = fopen(file_name, "r");

    if (file == NULL) {
      fprintf(stderr, "File couldn't be opened");
      return 1;
    }

    char line[LINE_LENGTH_LIMIT];

    while (fgets(line, sizeof(line), file)) {
      printf("%s", line);
    }

    fclose(file);

  } else {
    fprintf(stderr, "Invalid number of arguments!");
    return 1;
  }
}
