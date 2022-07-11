//* gcc -o output main.c stack.c gettop.c getch.c && output

#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "calc.h"

#define MAXOP 100 /* max size of operand or operator */

void printtop(void);
void duplicatetop(void);
void swaptoptwo(void);
void clearstack(void);

int main() {

    int type;
    double op2;
    char s[MAXOP]; // string buffer

    while ((type = getop(s)) != EOF) {

        switch (type) {
        case NUMBER:
            push(atof(s));
            break;
        case '+':
            // pop twice to get the two operands
            push(pop() + pop());
            break;
        case '*':
            push(pop() * pop());
            break;
        case '-':
            // need to pop and store the first operand bc - is unary:
            op2 = pop();
            push(pop() - op2);
            break;
        case '/':
            op2 = pop();
            if (op2 != 0.0)
                push(pop() / op2);
            else
                printf("error: zero divisor\n");
            break;
        case '%':
            op2 = pop();
            if (op2 != 0.0)
                // fmod returns the remainder of the division of the first operand by the second operand:
                push(fmod(pop(), op2));
            else
                printf("error: zero divisor\n");
            break;

        case '?':
            printtop();
            break;
        case '#':
            duplicatetop();
            break;
        case '~':
            swaptoptwo();
            break;
        case '!':
            clearstack();
            break;

        case '\n':
            // %g (Simplified scientific notation) prints the number with the simpler format between %e (scientific notation) and %f (floating point):
            printf("\t%.8g\n", pop());
            break;
        default:
            printf("error: unknown command %s\n", s);
            break;
        }
    }

    return 0;
}
