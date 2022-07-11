// Sometimes the program cannot determine that it has read enough input until it has read too much. One instance is collecting the characters that make up a number, until the first non-digit character is found. But then the program has read one character too far, a character that it is not prepared for. The solution is to 'un-read' the character that was read too far. This is done by putting it back into the buffer using ungetch().

#include <stdio.h>

#define BUFSIZE 100

char buf[BUFSIZE]; /* buffer for ungetch */
int bufp = 0;      /* next free position in buf */

/**
 * @brief Get a character from the input.
 *
 * @return int character
 */
int getch(void) {
    return (bufp > 0) ? buf[--bufp] : getchar();
}

/**
 * @brief Push a character back into the input.
 * The standard library includes a function ungetc that provides one character of pushback.
 * @param c character to push back
 */
void ungetch(int c) {
    if (bufp >= BUFSIZE)
        printf("ungetch: too many characters\n");
    else
        buf[bufp++] = c;
}