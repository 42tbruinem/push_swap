/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   memory.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbruinem <tbruinem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/29 16:26:07 by tbruinem      #+#    #+#                 */
/*   Updated: 2021/04/02 20:19:50 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <push_swap.h>
#include <stdlib.h>
#include <stdio.h>

/*
**		UTILS
*/

int		util_strcmp(char *str, char *s2)
{
	size_t	i;

	i = 0;
	while ((str[i] && s2[i]) && str[i] == s2[i])
		i++;
	return (str[i] == 0 && s2[i] == 0) ? 0 : str[i] - s2[i];
}

int		error(char *errstr, size_t errstr_size, int exit_status)
{
	write(2, errstr, errstr_size);
	return (exit_status);
}

/*
**		MEMORY_FUNCTIONS
*/

bool	memory_check(t_memory *memory)
{
	return (lstack_check(memory->a) && lstack_check(memory->b));
}

void	memory_print(t_memory *memory)
{
	astack_print("STACK A: ", sizeof("STACK A: "), memory->a);
	astack_print("STACK B: ", sizeof("STACK B: "), memory->b);
//	lstack_print("STACK A: ", sizeof("STACK A: "), memory->a);
//	lstack_print("STACK B: ", sizeof("STACK B: "), memory->b);
}

int		memory_init(t_memory *memory, int *content, size_t capacity)
{
	memory->a = astack_init(capacity, content, true);
	if (!memory->a)
		return (0);
	memory->b = astack_init(capacity, content, false);
	if (!memory->b)
		return (0);
	memory->operations = astack_operations();
	return (1);
}

ssize_t	memory_get_operation(char *operation)
{
	size_t			i;
	static const	char *op_names[] = {
		[OP_SA] = "sa",
		[OP_SB] = "sb",
		[OP_SS] = "ss",
		[OP_PA] = "pa",
		[OP_PB] = "pb",
		[OP_RA] = "ra",
		[OP_RB] = "rb",
		[OP_RR] = "rr",
		[OP_RRA] = "rra",
		[OP_RRB] = "rrb",
		[OP_RRR] = "rrr",
	};
	i = 0;
	while (i < sizeof(op_names) / sizeof(char *))
	{
		if (!util_strcmp(operation, (char *)op_names[i]))
			return (i);
		i++;
	}
	return (-1);
}

void	memory_perform_operation(t_memory *memory, char *operation)
{
	ssize_t			index;
	index = memory_get_operation(operation);
	if (index == -1)
		exit(error(ERR_INVALID_OP, sizeof(ERR_INVALID_OP), 1));
	memory->operations[index](memory);
}

void	memory_destroy(t_memory *memory)
{
	astack_destroy(memory->a);
	astack_destroy(memory->b);
	memory->a = NULL;
	memory->b = NULL;
}
