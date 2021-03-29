/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   memory.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbruinem <tbruinem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/29 16:26:07 by tbruinem      #+#    #+#                 */
/*   Updated: 2021/03/29 18:11:16 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <push_swap.h>
#include <stdlib.h>

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
**		OPERATIONS
*/

void	sa(t_memory *memory)
{
	stack_swap(memory->a);
}
void	sb(t_memory *memory)
{
	stack_swap(memory->b);
}
void	ss(t_memory *memory)
{
	sa(memory);
	sb(memory);
}
void 	pa(t_memory *memory)
{
	t_list	*top_of_b;

	top_of_b = stack_popfront(memory->b);
	if (!top_of_b)
		return ;
	stack_pushfront(memory->a, top_of_b);
}
void	pb(t_memory *memory)
{
	t_list	*top_of_a;

	top_of_a = stack_popfront(memory->a);
	if (!top_of_a)
		return ;
	stack_pushfront(memory->b, top_of_a);
}
void	ra(t_memory *memory)
{
	t_list	*old_top;

	old_top = stack_popfront(memory->a);
	stack_pushback(memory->a, old_top);
}
void	rb(t_memory *memory)
{
	t_list	*old_top;

	old_top = stack_popfront(memory->b);
	stack_pushback(memory->b, old_top);
}
void	rr(t_memory *memory)
{
	ra(memory);
	rb(memory);
}
void	rra(t_memory *memory)
{
	t_list	*old_bottom;

	old_bottom = stack_popback(memory->a);
	stack_pushfront(memory->a, old_bottom);
}
void	rrb(t_memory *memory)
{
	t_list	*old_bottom;

	old_bottom = stack_popback(memory->b);
	stack_pushfront(memory->b, old_bottom);
}
void	rrr(t_memory *memory)
{
	rra(memory);
	rrb(memory);
}

/*
**		MEMORY_FUNCTIONS
*/

int		memory_init(t_memory *memory, int *content, size_t size)
{
	memory->a = stack_init(size, content);
	if (!memory->a)
		return (0);
	memory->b = stack_init(0, NULL);
	if (!memory->b)
		return (0);
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
	}
	return (-1);
}

void	memory_perform_operation(t_memory *memory, char *operation)
{
	ssize_t			index;
	static const	t_operation		operations[] = {
		[OP_SA] = &sa,
		[OP_SB] = &sb,
		[OP_SS] = &ss,
		[OP_PA] = &pa,
		[OP_PB] = &pb,
		[OP_RA] = &ra,
		[OP_RB] = &rb,
		[OP_RR] = &rr,
		[OP_RRA] = &rra,
		[OP_RRB] = &rrb,
		[OP_RRR] = &rrr,
	};
	index = memory_get_operation(operation);
	if (index == -1)
		exit(error(ERR_INVALID_OP, sizeof(ERR_INVALID_OP), 1));
	operations[index](memory);
}

void	memory_destroy(t_memory *memory)
{
	stack_destroy(memory->a);
	stack_destroy(memory->b);
	memory->a = NULL;
	memory->b = NULL;
}
