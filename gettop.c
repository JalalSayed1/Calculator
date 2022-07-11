
#include "calc.h"
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>


/**
 * @brief Get a character from the input.
 *
 * @return int number or operator
 */
int getop(char s[]) {
    int i, c;

    // skip whitespace:
    while ((s[0] = c = getch()) == ' ' || c == '\t')
        ;
    s[1] = '\0';

    if (!isdigit(c) && c != '.' && c != '-')
        return c; // not a number, return the operator

    i = 0;

    // - sign could mean negative number or unary operator:
    if (c == '-') {
        // if the first character is a '-', then it is a unary operator:
        if (isdigit(c = getch()) || c == '.') {
            s[++i] = c;
        } else {
            ungetch(c);
            return '-';
        }
    }

    if (isdigit(c)) // collect integer part
        // get next char and add it to the string buffer s:
        while (isdigit(s[++i] = c = getch()))
            ;

    // if last character is a decimal point, collect fractional part:
    if (c == '.') // collect fraction part
        while (isdigit(s[++i] = c = getch()))
            ;

    s[i] = '\0';
    // if last char is not ESF, means we have read one char too far. So we need to ungetch() it:
    if (c != EOF)
        ungetch(c);
    return NUMBER;
}