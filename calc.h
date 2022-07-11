#ifndef CALC_H
#define CALC_H


void push(double);
double pop(void);
int getop(char[]);
int getch(void);
void ungetch(int);

#define NUMBER '0' /* signal that a number was found */

#endif /* CALC_H */