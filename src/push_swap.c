/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   push_swap.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbruinem <tbruinem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/29 15:39:04 by tbruinem      #+#    #+#                 */
/*   Updated: 2021/04/02 15:56:59 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <push_swap.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

void	perform_op(t_memory *memory, char *operation)
{
	size_t	operation_length;

	operation_length = (!operation) ? 0 : util_strlen(operation);

	printf("      %s      \n", operation);
	printf("------");
	for (size_t i = 0; i < operation_length; i++)
		printf("%c", '-');
	printf("------\n");
	if (operation)
		memory_perform_operation(memory, operation);
	memory_print(memory);
	printf("------");
	for (size_t i = 0; i < operation_length; i++)
		printf("%c", '-');
	printf("------\n");
}

int main(int argc, char **argv)
{
	t_memory	memory;
	int			*content;
	size_t		capacity;

	if (argc == 1)
		return (error(ERR_INVALID_ARG, sizeof(ERR_INVALID_ARG), 1));
	content = parse_input(&capacity, argc, argv);
	if (!content || !memory_init(&memory, content, capacity))
		return (error(ERR_MEMFAIL, sizeof(ERR_MEMFAIL), 1));
	free(content);
	memory_print(&memory);
	astack_rotate(memory.a, -1);
	memory_print(&memory);
	astack_swap(memory.a);
	memory_print(&memory);
	astack_rotate(memory.a, 1);
	memory_print(&memory);
	astack_push(memory.a, memory.b);
	memory_print(&memory);
	// memory_print(&memory);
	// astack_rotate(memory.a);
	// memory_print(&memory);
	// astack_rotate(memory.a);
	// memory_print(&memory);
	// perform_op(&memory, NULL);
	// perform_op(&memory, "rb");
	// perform_op(&memory, "ra");
	// perform_op(&memory, "sa");
	// perform_op(&memory, "pb");
	// perform_op(&memory, "pa");
	// perform_op(&memory, "pb");
	// perform_op(&memory, "pb");
	// perform_op(&memory, "pb");
	// perform_op(&memory, "rb");
	// perform_op(&memory, "sb");
	// perform_op(&memory, "rra");
	memory_destroy(&memory);
	return (0);
}
