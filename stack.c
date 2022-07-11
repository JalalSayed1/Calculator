#include "calc.h"
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define MAXVAL 100 /* maximum depth of val stack */

int sp = 0;         /* next free stack position */
double val[MAXVAL]; /* value stack */

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
 * @brief print top of the stack with popping it.
 *
 */
void printtop(void) {
    printf("\t%.8g\n", val[sp - 1]);
}

/**
 * @brief duplicate top element of the stack.
 *
 */
void duplicatetop(void) {
    push(val[sp - 1]);
}

/**
 * @brief swap top two elements of the stack.
 *
 */
void swaptoptwo(void) {
    double temp = val[sp - 1];
    val[sp - 1] = val[sp - 2];
    val[sp - 2] = temp;
}

/**
 * @brief clear the stack.
 *
 */
void clearstack(void) {
    sp = 0;
}
