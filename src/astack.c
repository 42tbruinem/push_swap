/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   astack.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbruinem <tbruinem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/04/02 13:26:48 by tbruinem      #+#    #+#                 */
/*   Updated: 2021/04/02 21:35:52 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

void		astack_print(char *title, size_t title_size, t_astack *stack)
{
	size_t	i;
	size_t	elements;

	elements = 0;
	i = stack->start;
	printf("start: %ld | end: %ld\n", stack->start, stack->end);
	write(1, title, title_size);
	while (elements < stack->size)
	{
		util_putnum(stack->data[i]);
		if (elements + 1 != stack->size)
			write(1, " ", 1);
		i = util_cap(i, 1, stack->capacity);
		elements++;
	}
	write(1, "\n", 1);
}

void		astack_rotate(t_astack *stack, int increment)
{
	if (stack->size < 2)
		return ;
	stack->end = util_cap(stack->end, increment, stack->capacity);
	stack->start = util_cap(stack->start, increment, stack->capacity);
}

void		astack_swap(t_astack *stack)
{
	int	tmp;

	if (stack->size < 2)
		return ;
	tmp = stack->data[stack->start];
	stack->data[stack->start] = stack->data[util_cap(stack->start, 1, stack->capacity)];
	stack->data[util_cap(stack->start, 1, stack->capacity)] = tmp;
}

void		astack_push(t_astack *from, t_astack *to)
{
	if (from->size < 1)
		return ;
	to->start = util_cap(to->start, -1, to->capacity);
	to->data[to->start] = from->data[from->start];
	from->start = util_cap(from->start, 1, from->capacity);
	to->size++;
	from->size--;
}

void		astack_destroy(t_astack *stack)
{
	free(stack->data);
	free(stack);
}

t_astack	*astack_init(size_t capacity, int *content, bool a)
{
	t_astack	*stack;

	stack = malloc(sizeof(t_astack));
	if (!stack)
		return (NULL);
	stack->data = util_memdup(content, capacity * sizeof(int));
	if (!stack->data)
	{
		free(stack);
		return (NULL);
	}
	if (a)
	{
		stack->end = capacity - 1;
		stack->size = capacity;
	}
	else
	{
		stack->end = 0;
		stack->size = 0;
	}
	stack->capacity = capacity;
	stack->start = 0;
	return (stack);
}

/*
**	OPERATIONS
*/

void	astack_sa(t_memory *memory)
{
	astack_swap(memory->a);
}
void	astack_sb(t_memory *memory)
{
	astack_swap(memory->b);
}
void	astack_ss(t_memory *memory)
{
	astack_sa(memory);
	astack_sb(memory);
}
void	astack_pa(t_memory *memory)
{
	astack_push(memory->b, memory->a);
}
void	astack_pb(t_memory *memory)
{
	astack_push(memory->a, memory->b);
}
void	astack_ra(t_memory *memory)
{
	astack_rotate(memory->a, 1);
}
void	astack_rb(t_memory *memory)
{
	astack_rotate(memory->b, 1);
}
void	astack_rr(t_memory *memory)
{
	astack_rb(memory);
	astack_ra(memory);
}
void	astack_rra(t_memory *memory)
{
	astack_rotate(memory->a, -1);
}
void	astack_rrb(t_memory *memory)
{
	astack_rotate(memory->b, -1);
}
void	astack_rrr(t_memory *memory)
{
	astack_rrb(memory);
	astack_rra(memory);
}

t_operation	*astack_operations(void)
{
	static t_operation		operations[] = {
		[OP_SA] = &astack_sa,
		[OP_SB] = &astack_sb,
		[OP_SS] = &astack_ss,
		[OP_PA] = &astack_pa,
		[OP_PB] = &astack_pb,
		[OP_RA] = &astack_ra,
		[OP_RB] = &astack_rb,
		[OP_RR] = &astack_rr,
		[OP_RRA] = &astack_rra,
		[OP_RRB] = &astack_rrb,
		[OP_RRR] = &astack_rrr,
	};
	return (operations);
}
