# APC Big Integer Calculator

## Overview
The APC Big Integer Calculator is a C program that performs arithmetic
operations on very large integers which cannot be stored using standard
C data types. The program represents each digit of the number using a
Doubly Linked List and performs operations similar to manual calculations.

## Features
The calculator supports the following operations:

1. Addition (+)
2. Subtraction (-)
3. Multiplication (*)
4. Division (/)

## Implementation
Each digit of a number is stored in a node of a Doubly Linked List.

Example representation of number 12345:

Head -> 1 <-> 2 <-> 3 <-> 4 <-> 5 -> Tail

Arithmetic operations are performed starting from the least significant
digit (tail) and moving towards the head.

## Project Files

main.c
Handles program execution and user input.

main.h
Contains structure definitions and function declarations.

apc.c
Contains implementation of addition, subtraction,
multiplication and division operations.

## Compilation

Use gcc compiler to compile the program:

gcc main.c apc.c -o calc

## Usage

Run the program using command line arguments:

./a.out <operand1> <operator> <operand2>

Example:
./calc 123456789 + 987654321

Output:

1111111110

## Concepts Used
- Doubly Linked List
- Dynamic Memory Allocation
- Pointer Manipulation
- Big Integer Arithmetic
- Command Line Arguments

## Author
Indira Krupadarshini Midde
