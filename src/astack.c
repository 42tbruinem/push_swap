/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   astack.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbruinem <tbruinem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/04/02 13:26:48 by tbruinem      #+#    #+#                 */
/*   Updated: 2021/04/02 19:19:30 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include <stdlib.h>
#include <unistd.h>

void		astack_print(char *title, size_t title_size, t_astack *stack)
{
	size_t	i;
	size_t	elements;

	elements = 0;
	i = stack->start;
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
	if (stack->capacity < 2)
		return ;
	stack->end = util_cap(stack->end, increment, stack->capacity);
	stack->start = util_cap(stack->start, increment, stack->capacity);
}

void		astack_swap(t_astack *stack)
{
	int	tmp;

	tmp = stack->data[stack->start];
	stack->data[stack->start] = stack->data[(stack->start + 1) % stack->capacity];
	stack->data[(stack->start + 1) % stack->capacity] = tmp;
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
