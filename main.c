#include "monty.h"
stack_t *stackHead = NULL;

/**
 * main - Entry point of the program.
 * @argc: Number of command-line arguments.
 * @argv: Array of command-line argument strings.
 * Return: Always 0.
 */
int main(int argc, char *argv[])
{
    if (argc != 2) {
        fprintf(stderr, "USAGE: monty file\n");
        exit(EXIT_FAILURE);
    }
    open_file(argv[1]);
    free_nodes();
    return 0;
}

/**
 * createNode - Creates a new node.
 * @value: The value to be stored in the node.
 * Return: A pointer to the newly created node on success, otherwise NULL.
 */
stack_t *createNode(int value)
{
    stack_t *newNode;

    newNode = malloc(sizeof(stack_t));
    if (newNode == NULL)
        err(4);

    newNode->next = NULL;
    newNode->prev = NULL;
    newNode->n = value;

    return newNode;
}

/**
 * freeNodes - Frees all nodes in the stack.
 */
void free_nodes(void)
{
    stack_t *tempNode;

    if (stackHead == NULL)
        return;

    while (stackHead != NULL) {
        tempNode = stackHead;
        stackHead = stackHead->next;
        free(tempNode);
    }
}

/**
 * addToQueue - Adds a node to the end of the queue.
 * @newNode: Pointer to the new node.
 * @lineNumber: Line number of the opcode (unused in this function).
 */
void addToQueue(stack_t **newNode, __attribute__((unused)) unsigned int lineNumber)
{
    stack_t *tempNode;

    if (newNode == NULL || *newNode == NULL)
        exit(EXIT_FAILURE);

    if (stackHead == NULL) {
        stackHead = *newNode;
        return;
    }

    tempNode = stackHead;
    while (tempNode->next != NULL)
        tempNode = tempNode->next;

    tempNode->next = *newNode;
    (*newNode)->prev = tempNode;
}
