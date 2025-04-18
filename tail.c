#include <stdio.h>
#include <stdlib.h>

#define LINE_LENGTH_LIMIT 4096

struct CircBuffer {
  
};

// size = lines
struct CircBuffer* cbuf_create(size_t size) {
  struct CircBuffer *buffer;

  return buffer;
}

void cbuf_put(struct CircBuffer *buffer, const char *line) {

}

char* cbuf_get(struct CircBuffer *buffer) {

}

void cbuf_free(struct CircBuffer *buffer) {
  free(buffer);
}

int main(const int argc, char *argv[]) {
  if (argc == 1) {
    // read from stdio
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
