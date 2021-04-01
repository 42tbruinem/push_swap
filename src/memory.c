/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   memory.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbruinem <tbruinem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/29 16:26:07 by tbruinem      #+#    #+#                 */
/*   Updated: 2021/04/01 21:31:15 by tbruinem      ########   odam.nl         */
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
**		OPERATIONS
*/

void	lstack_sa(t_memory *memory)
{
	stack_swap(memory->a);
}
void	lstack_sb(t_memory *memory)
{
	stack_swap(memory->b);
}
void	lstack_ss(t_memory *memory)
{
	lstack_sa(memory);
	lstack_sb(memory);
}
void 	lstack_pa(t_memory *memory)
{
	t_list	*top_of_b;

	if (memory->b->size < 1)
		return ;
	top_of_b = stack_popfront(memory->b);
	if (!top_of_b)
		return ;
	stack_pushfront(memory->a, top_of_b);
}
void	lstack_pb(t_memory *memory)
{
	t_list	*top_of_a;

	if (memory->a->size < 1)
		return ;
	top_of_a = stack_popfront(memory->a);
	if (!top_of_a)
		return ;
	stack_pushfront(memory->b, top_of_a);
}
void	lstack_ra(t_memory *memory)
{
	t_list	*old_top;

	if (memory->a->size < 2)
		return ;
	old_top = stack_popfront(memory->a);
	stack_pushback(memory->a, old_top);
}
void	lstack_rb(t_memory *memory)
{
	t_list	*old_top;

	if (memory->b->size < 2)
		return ;
	old_top = stack_popfront(memory->b);
	stack_pushback(memory->b, old_top);
}
void	lstack_rr(t_memory *memory)
{
	lstack_ra(memory);
	lstack_rb(memory);
}
void	lstack_rra(t_memory *memory)
{
	t_list	*old_bottom;

	if (memory->a->size < 2)
		return ;
	old_bottom = stack_popback(memory->a);
	stack_pushfront(memory->a, old_bottom);
}
void	lstack_rrb(t_memory *memory)
{
	t_list	*old_bottom;

	if (memory->b->size < 2)
		return ;
	old_bottom = stack_popback(memory->b);
	stack_pushfront(memory->b, old_bottom);
}
void	lstack_rrr(t_memory *memory)
{
	lstack_rra(memory);
	lstack_rrb(memory);
}

/*
**		MEMORY_FUNCTIONS
*/

bool	memory_check(t_memory *memory)
{
	return (stack_check(memory->a) && stack_check(memory->b));
}

void	memory_print(t_memory *memory)
{
	stack_print("STACK A: ", sizeof("STACK A: "), memory->a);
	stack_print("STACK B: ", sizeof("STACK B: "), memory->b);
}

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
		i++;
	}
	return (-1);
}

void	memory_perform_operation(t_memory *memory, char *operation)
{
	ssize_t			index;
	static const	t_operation		operations[] = {
		[OP_SA] = &lstack_sa,
		[OP_SB] = &lstack_sb,
		[OP_SS] = &lstack_ss,
		[OP_PA] = &lstack_pa,
		[OP_PB] = &lstack_pb,
		[OP_RA] = &lstack_ra,
		[OP_RB] = &lstack_rb,
		[OP_RR] = &lstack_rr,
		[OP_RRA] = &lstack_rra,
		[OP_RRB] = &lstack_rrb,
		[OP_RRR] = &lstack_rrr,
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
