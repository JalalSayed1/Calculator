//* gcc -o calculator calculator.c && calculator

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h> /* for atof() */
#include <math.h>

#define MAXOP 100  /* max size of operand or operator */
#define NUMBER '0' /* signal that a number was found */
#define MAXVAL 100 /* maximum depth of val stack */
#define BUFSIZE 100

int sp = 0;         /* next free stack position */
double val[MAXVAL]; /* value stack */
char buf[BUFSIZE];  /* buffer for ungetch */
int bufp = 0;       /* next free position in buf */

int getop(char[]);
void push(double);
double pop(void);
int getch(void);
// Sometimes the program cannot determine that it has read enough input until it has read too much. One instance is collecting the characters that make up a number, until the first non-digit character is found. But then the program has read one character too far, a character that it is not prepared for. The solution is to 'un-read' the character that was read too far. This is done by putting it back into the buffer using ungetch().
void ungetch(int);

/**
 * @brief Reverse Polish calculator
 *
 * @return int
 */
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

/**
 * @brief Push f into the stack.
 *
 * @param f floating point number to push
 */
void push(double f) {
    if (sp < MAXVAL)
        val[sp++] = f;
    else
        printf("error: stack full, can't push %g\n", f);
}

/**
 * @brief Pop and return the top value from the stack.
 *
 * @return double top value from the stack
 */
double pop(void) {
    if (sp > 0)
        return val[--sp];
    else {
        printf("error: stack empty\n");
        return 0.0;
    }
}

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
