#include "monty.h"

/**
 * printAscii - Prints the ASCII value.
 * @stack: Pointer to a pointer pointing to the top node of the stack.
 * @lineNumber: Integer representing the line number of the opcode.
 */
void printAscii(stack_t **stack, unsigned int lineNumber)
{
    int ascii;

    if (stack == NULL || *stack == NULL)
        string_err(11, lineNumber);

    ascii = (*stack)->n;

    if (ascii < 0 || ascii > 127)
        string_err(10, lineNumber);

    printf("%c\n", ascii);
}

/**
 * printString - Prints a string.
 * @stack: Pointer to a pointer pointing to the top node of the stack.
 * @lineNumber: Integer representing the line number of the opcode.
 */
void printString(stack_t **stack, __attribute__((unused)) unsigned int lineNumber)
{
    int ascii;
    stack_t *temp;

    if (stack == NULL || *stack == NULL)
    {
        printf("\n");
        return;
    }

    temp = *stack;
    while (temp != NULL) {
        ascii = temp->n;
        if (ascii <= 0 || ascii > 127)
            break;
        printf("%c", ascii);
        temp = temp->next;
    }

    printf("\n");
}

/**
 * rotateLeft - Rotates the first node of the stack to the bottom.
 * @stack: Pointer to a pointer pointing to the top node of the stack.
 * @lineNumber: Integer representing the line number of the opcode.
 */
void rotateLeft(stack_t **stack, __attribute__((unused)) unsigned int lineNumber)
{
    stack_t *temp;

    if (stack == NULL || *stack == NULL || (*stack)->next == NULL)
        return;

    temp = *stack;

    while (temp->next != NULL)
        temp = temp->next;

    temp->next = *stack;
    (*stack)->prev = temp;
    *stack = (*stack)->next;
    (*stack)->prev->next = NULL;
    (*stack)->prev = NULL;
}

/**
 * rotateRight - Rotates the last node of the stack to the top.
 * @stack: Pointer to a pointer pointing to the top node of the stack.
 * @lineNumber: Integer representing the line number of the opcode.
 */
void rotateRight(stack_t **stack, __attribute__((unused)) unsigned int lineNumber)
{
    stack_t *temp;

    if (stack == NULL || *stack == NULL || (*stack)->next == NULL)
        return;

    temp = *stack;

    while (temp->next != NULL)
        temp = temp->next;

    temp->next = *stack;
    temp->prev->next = NULL;
    temp->prev = NULL;
    (*stack)->prev = temp;
    (*stack) = temp;
}
