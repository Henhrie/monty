#include "monty.h"

/**
 * doNothing - Does nothing.
 * @stack: Pointer to a pointer pointing to the top node of the stack.
 * @lineNumber: Integer representing the line number of the opcode.
 */
void doNothing(stack_t **stack, unsigned int lineNumber)
{
    (void)stack;
    (void)lineNumber;
}

/**
 * swapNodes - Swaps the top two elements of the stack.
 * @stack: Pointer to a pointer pointing to the top node of the stack.
 * @lineNumber: Integer representing the line number of the opcode.
 */
void swapNodes(stack_t **stack, unsigned int lineNumber)
{
    stack_t *temp;

    if (stack == NULL || *stack == NULL || (*stack)->next == NULL)
        more_err(8, lineNumber, "swap");

    temp = (*stack)->next;
    (*stack)->next = temp->next;

    if (temp->next != NULL)
        temp->next->prev = *stack;

    temp->next = *stack;
    (*stack)->prev = temp;
    temp->prev = NULL;
    *stack = temp;
}

/**
 * addNodes - Adds the top two elements of the stack.
 * @stack: Pointer to a pointer pointing to the top node of the stack.
 * @lineNumber: Integer representing the line number of the opcode.
 */
void addNodes(stack_t **stack, unsigned int lineNumber)
{
    int sum;

    if (stack == NULL || *stack == NULL || (*stack)->next == NULL)
        more_err(8, lineNumber, "add");

    (*stack) = (*stack)->next;
    sum = (*stack)->n + (*stack)->prev->n;
    (*stack)->n = sum;

    free((*stack)->prev);
    (*stack)->prev = NULL;
}

/**
 * subNodes - Subtracts the top two elements of the stack.
 * @stack: Pointer to a pointer pointing to the top node of the stack.
 * @lineNumber: Integer representing the line number of the opcode.
 */
void subNodes(stack_t **stack, unsigned int lineNumber)
{
    int difference;

    if (stack == NULL || *stack == NULL || (*stack)->next == NULL)
        more_err(8, lineNumber, "sub");

    (*stack) = (*stack)->next;
    difference = (*stack)->n - (*stack)->prev->n;
    (*stack)->n = difference;

    free((*stack)->prev);
    (*stack)->prev = NULL;
}

/**
 * divNodes - Divides the top two elements of the stack.
 * @stack: Pointer to a pointer pointing to the top node of the stack.
 * @lineNumber: Integer representing the line number of the opcode.
 */
void divNodes(stack_t **stack, unsigned int lineNumber)
{
    int quotient;

    if (stack == NULL || *stack == NULL || (*stack)->next == NULL)
        more_err(8, lineNumber, "div");

    if ((*stack)->n == 0)
        more_err(9, lineNumber);

    (*stack) = (*stack)->next;
    quotient = (*stack)->n / (*stack)->prev->n;
    (*stack)->n = quotient;

    free((*stack)->prev);
    (*stack)->prev = NULL;
}
