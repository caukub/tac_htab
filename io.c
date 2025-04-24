#include <ctype.h>
#include <stdio.h>

int read_word(unsigned max, char s[max], FILE *f) {
    unsigned word_length = 0;

    int ch;

    while ((ch = getc(f)) != EOF && isspace(ch)) {}

    if (ch == EOF) {
        return EOF;
    }

    // TODO - prepsat na do while (funkcne v poradku ale nehezke)
    while ((ch = getc(f)) != EOF && !isspace(ch)) {
        if (word_length < max - 1) {
            s[word_length] = ch;
            word_length += 1;
        }
    }

    s[word_length] = '\0';

    word_length += 1;

    return word_length;
}