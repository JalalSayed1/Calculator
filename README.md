# Calculator
Calculator program that provides the operators +, -, * and / as well as modulus %, print last result ?, duplicate last result #, swap last two results ~ and clear stack (memory) !. . It uses the reverse Polish notation. Section 4.3 of The C Programming Language. 

## Reverse Polish notation:
- Each operator follows its operands; an infix expression like (1-2) * (4+5) is entered as 1 2 - 4 5 + *
- Parentheses are not needed; the notation is unambigueis as long as we know how many oprands each operator expects.
- Impllementation: Each oprand is pushed onto a stack; when an operator arrives, the proper number of operands (two for binary operators) is popped, the operator is applied to them, and the result is pushed back onto the stack.
- For instance, in the example above, 1 and 2 are pushed, then replaced by their difference -1. Next, 4 and 5 are pushed and then replaced by their sum 9. The product of -1 and 9, which is -9, replaces them on the stack. The value on the top of the stack is popped and printed when the end of the input line is encounted.

## Structure of the program:
```
while (next operator or operand is not end-of-file indicator)
  if (number)
    push it
  else if (operand)
    pop operands
    do operation
    push result
  else if (newline)
    pop and print tor of stack
  else
    error
```
## Result example:
![image](https://user-images.githubusercontent.com/92950538/177803444-2e7c0df5-5bd5-4e71-96fe-e8d0c603ade9.png)


