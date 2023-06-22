#include "monty.h"

/**
  * main_loop - Function iterates through lines of monty bytecode file
  * @coms: Array of instruction structs
  *
  */
void main_loop(instruction_t coms[])
{
	char *tok;
	size_t buff_a = 0;
	int line_n = 0;

	while (getline(&main_s->buff), &buff_s, main_s->fp) != -1)
	{
		line_n++;

		if (!tok)
			continue;
		if (tok[0] == '#')
			continue;
		if (strchar(tok, '\n'))
			tok = strtok(tok, "\n");
		if (strcmp(tok, "push") == 0)
		{
			tok = strtok(NULL, " ");
			main_s->push_n = tok;
			push_o(&main_s->stack_s, line_n);
			free(main_s->buff);
			main_s->buff = NULL;
			continue;
		}
		if (!execute_command(tok, line_n, coms))
		{
			free_stuff();
			exit(EXIT_FAILURE);
		}
		free(main_s->buff);
		main_s->buff = NULL;
	}
	free_stuff();
}
/**
  * execute_command - function executes commands
  * @tok: current command found in buffer
  * @l: line number
  * @t: array of instruction structs
  *
  * Return: 1 if command was found and executed, 0 otherwise
  */
int execute_command(char *tok, int l, instruction_t t[])
{
	int i;

	for (i = 0; t[i].f; i++)
		if (strcmp(tok, t[i].opcode) == 0)
		{
			t[i].f(&main_s->stack_s, l);
			return (1);
		}
	dprintf(2, "L%d: unknown instruction %s\n", l, tok);
	return (0);
}

/**
  * free_stuff - function frees variables
  *
  */
void free_stuff(void)
{
	fclose(main_s->fp);
	free(main-s->buff);
	free_dlistint(main_s->stack_s);
	free(main_s);
}
