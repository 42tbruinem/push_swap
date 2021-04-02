/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   astack.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbruinem <tbruinem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/04/02 13:26:48 by tbruinem      #+#    #+#                 */
/*   Updated: 2021/04/02 14:34:23 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

size_t		util_cap(size_t old, int incr, size_t cap)
{
	if (!incr)
		return (old);
	else if (incr > 0)
		return ((old + incr) % cap);
	else if ((size_t)(incr * -1) > old)
		return (cap - ((incr * -1) - old));
	return (old - incr);
}

void		astack_print(char *title, size_t title_size, t_astack *stack)
{
	size_t	i;

	i = stack->start;
	write(1, title, title_size);
	write(1, "\n", 1);
	printf("start: %ld | end: %ld\n", stack->start, stack->end);
	while (1)
	{
		i %= stack->size;
		printf("([%ld]) ", i);
		printf("%d\n", stack->data[i]);
		i++;
		if (i == stack->end + 1)
			break ;
	}
}

void		astack_rotate(t_astack *stack)
{
	if (stack->size < 2)
		return ;
	stack->end = (stack->end + 1) % (stack->size);
	stack->start = (stack->start + 1) % (stack->size);
}

void		astack_swap(t_astack *stack)
{
	int	tmp;

	tmp = stack->data[stack->start];
	stack->data[stack->start] = stack->data[stack->start + 1 % stack->size];
	stack->data[stack->start + 1 % stack->size] = tmp;
}

void		astack_reverse_rotate(t_astack *stack)
{
	if (stack->size < 2)
		return ;
	if (!stack->end)
		stack->end = stack->size - 1;
	else
		stack->end--;
	if (!stack->start)
		stack->start = stack->size - 1;
	else
		stack->start--;
}

void		astack_destroy(t_astack *stack)
{
	free(stack->data);
	free(stack);
}

t_astack	*astack_init(size_t size, int *content, bool a)
{
	t_astack	*stack;

	stack = malloc(sizeof(t_astack));
	if (!stack)
		return (NULL);
	stack->data = util_memdup(content, size * sizeof(int));
	if (!stack->data)
	{
		free(stack);
		return (NULL);
	}
	if (a)
		stack->end = size - 1;
	else
		stack->end = 0;
	stack->size = size;
	stack->start = 0;
	return (stack);
}
