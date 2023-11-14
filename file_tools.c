#include "monty.h"
#include <stdio.h>

ssize_t get_line(char **lineptr, size_t *n, FILE *stream);
void call_fun(op_func func, char *op, char *val, int ln, int format);
stack_t *head;

/**
 * openAndReadFile - Opens and reads a file.
 * @filename: The file path.
 * Return: void
 */
void openAndReadFile(char *filename)
{
    FILE *fileDescriptor = fopen(filename, "r");

    if (filename == NULL || fileDescriptor == NULL)
        err(2, filename);

    read_file(fileDescriptor);
    fclose(fileDescriptor);
}

/**
 * readFile - Reads a file.
 * @fd: Pointer to the file descriptor.
 * Return: void
 */
void read_file(FILE *fd)
{
    int lineNumber, format = 0;
    char *buffer = NULL;
    size_t len = 0;

    for (lineNumber = 1; get_line(&buffer, &len, fd) != -1; lineNumber++)
    {
        format = parse_line(buffer, lineNumber, format);
    }
    free(buffer);
}

/**
 * parseLine - Separates each line into tokens to determine
 * which function to call.
 * @buffer: Line from the file.
 * @lineNumber: Line number.
 * @format: Storage format. If 0, Nodes will be entered as a stack.
 *          If 1, nodes will be entered as a queue.
 * Return: Returns 0 if the opcode is stack. 1 if queue.
 */
int parseLine(char *buffer, int lineNumber, int format)
{
    char *opcode, *value;
    const char *delim = "\n ";

    if (buffer == NULL)
        err(4);

    opcode = strtok(buffer, delim);
    if (opcode == NULL)
        return format;
    value = strtok(NULL, delim);

    if (strcmp(opcode, "stack") == 0)
        return 0;
    if (strcmp(opcode, "queue") == 0)
        return 1;

    find_func(opcode, value, lineNumber, format);
    return format;
}

/**
 * findFunction - Finds the appropriate function for the opcode.
 * @opcode: Opcode.
 * @value: Argument of the opcode.
 * @format: Storage format. If 0, Nodes will be entered as a stack.
 *          If 1, nodes will be entered as a queue.
 * @lineNumber: Line number.
 * Return: void
 */
void find_func(char *opcode, char *value, int lineNumber, int format)
{
    int i;
    int flag;

    instruction_t functionList[] = {
        {"push", add_to_stack},
        {"pall", print_stack},
        {"pint", print_top},
        {"pop", pop_top},
        {"nop", nop},
        {"swap", swap_nodes},
        {"add", add_nodes},
        {"sub", sub_nodes},
        {"div", div_nodes},
        {"mul", mul_nodes},
        {"mod", mod_nodes},
        {"pchar", print_char},
        {"pstr", print_str},
        {"rotl", rotl},
        {"rotr", rotr},
        {NULL, NULL}
    };

    if (opcode[0] == '#')
        return;

    for (flag = 1, i = 0; functionList[i].opcode != NULL; i++) {
        if (strcmp(opcode, functionList[i].opcode) == 0) {
            call_fun(functionList[i].f, opcode, value, lineNumber, format);
            flag = 0;
        }
    }
    if (flag == 1)
        err(3, lineNumber, opcode);
}

/**
 * callFunction - Calls the required function.
 * @func: Pointer to the function that is about to be called.
 * @op: String representing the opcode.
 * @val: String representing a numeric value.
 * @ln: Line number for the instruction.
 * @format: Format specifier. If 0, Nodes will be entered as a stack.
 *          If 1, nodes will be entered as a queue.
 */
void callFunction(op_func func, char *op, char *val, int ln, int format)
{
    stack_t *node;
    int flag;
    int i;

    flag = 1;
    if (strcmp(op, "push") == 0) {
        if (val != NULL && val[0] == '-')
        {
            val = val + 1;
            flag = -1;
        }
        if (val == NULL)
            err(5, ln);
        for (i = 0; val[i] != '\0'; i++)
        {
            if (isdigit(val[i]) == 0)
                err(5, ln);
        }
        node = create_node(atoi(val) * flag);
        if (format == 0)
            func(&node, ln);
        if (format == 1)
            add_to_queue(&node, ln);
    } else
        func(&head, ln);
}
