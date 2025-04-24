#include <ctype.h>
#include <stdio.h>

// TODO - prepsat na do while (funkcne v poradku ale nehezke)
int read_word(unsigned max, char s[max], FILE *f) {
    unsigned word_length = 0;

    int ch;

    while ((ch = getc(f)) != EOF && isspace(ch));

    if (ch == EOF) {
        return EOF;
    }

    if (word_length < max - 1) {
        s[word_length] = ch;
        word_length += 1;
    }

    while ((ch = getc(f)) != EOF && !isspace(ch)) {
        if (word_length < max - 1) {
            s[word_length] = ch;
            word_length += 1;
        }
    }

    s[word_length] = '\0';

    return word_length;
}