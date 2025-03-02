Description
This project implements an integer calculator that evaluates mathematical expressions using postfix notation. The calculator supports basic arithmetic operations, conditional expressions, and aggregate functions while correctly handling operator precedence and parentheses. The program reads expressions in infix notation, converts them to postfix notation, and evaluates them using a stack-based approach.

Features
Supports the following operations:
Addition (+), Subtraction (-)
Multiplication (*), Integer Division (/) (rounded down)
Unary Negation (N a)
Conditional Operation (IF(a, b, c)) – Returns b if a > 0, otherwise returns c
Aggregate Functions (MIN(a1, a2, ...), MAX(a1, a2, ...)) – Find the minimum/maximum of given values
Handles parentheses for operator precedence
Displays detailed step-by-step stack operations
Gracefully handles division by zero (ERROR message)
Efficient memory management
