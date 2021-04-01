/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   stack.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbruinem <tbruinem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/29 15:42:20 by tbruinem      #+#    #+#                 */
/*   Updated: 2021/04/01 20:21:15 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <push_swap.h>

#include <stdlib.h>
#include <stdio.h>

void	util_numprint(int nb)
{
	char			c;
	unsigned int	num;

	if (nb < 0)
	{
		write(1, "-", 1);
		num = nb * -1;
	}
	else
		num = nb;
	if ((int)num >= 10)
		util_numprint((int)num / 10);
	c = (num % 10) + '0';
	write(1, &c, 1);
}

void	stack_print(char *title, size_t title_size, t_lstack *stack)
{
	size_t	i;
	t_list	*begin;

	i = 0;
	begin = stack->head;
	write(1, title, title_size);
	while (begin)
	{
		util_numprint(begin->content);
		if (begin->next)
			write(1, " -> ", 4);
		i++;
		begin = begin->next;
	}
	write(1, "\n", 1);
}

t_list	*stack_popback(t_lstack *stack)
{
	t_list	*elem;

	if (!stack->size)
		return (NULL);
	if (stack->tail)
		stack->tail = stack->tail->prev;
	elem = list_popback(&stack->head);
	stack->size--;
	return (elem);
}

t_list	*stack_popfront(t_lstack *stack)
{
	t_list	*elem;

	if (!stack->size)
		return (NULL);
	if (stack->size == 1)
		stack->tail = NULL;
	elem = list_popfront(&stack->head);
	stack->size--;
	return (elem);
}

void	stack_pushback(t_lstack *stack, t_list *elem)
{
	if (!elem)
		exit(error(ERR_MEMFAIL, sizeof(ERR_MEMFAIL), 1));
	list_pushback(&stack->head, elem);
	stack->tail = elem;
	stack->size++;
}

void	stack_pushfront(t_lstack *stack, t_list *elem)
{
	list_pushfront(&stack->head, elem);
	if (stack->tail == NULL)
		stack->tail = stack->head;
	stack->size++;
}

void	stack_destroy(t_lstack *stack)
{
	list_clear(stack->head);
	free(stack);
}

void	stack_swap(t_lstack *stack)
{
	t_list	*one;
	t_list	*two;

	if (stack->size < 2)
		return ;
	one = stack_popfront(stack);
	two = stack_popfront(stack);
	stack_pushfront(stack, one);
	stack_pushfront(stack, two);
}

t_lstack	*stack_init(size_t size, int *content)
{
	t_lstack	*stack;
	size_t	i;

	stack = malloc(sizeof(t_lstack));
	if (!stack)
		return (NULL);
	stack->size = 0;
	stack->head = NULL;
	stack->tail = NULL;
	i = 0;
	while (i < size)
	{
		stack_pushback(stack, list_new(content[i]));
		i++;
	}
	return (stack);
}
