/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   stack.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbruinem <tbruinem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/29 15:42:20 by tbruinem      #+#    #+#                 */
/*   Updated: 2021/03/30 00:36:06 by tbruinem      ########   odam.nl         */
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

void	stack_print(char *title, size_t title_size, t_stack *stack)
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

t_list	*stack_popback(t_stack *stack)
{
	if (!stack->size)
		return (NULL);
	t_list	*elem;
	stack->tail = stack->tail->prev;
	elem = list_popback(&stack->head);
	stack->size--;
	return (elem);
}

t_list	*stack_popfront(t_stack *stack)
{
	if (!stack->size)
		return (NULL);
	t_list	*elem;
	if (stack->size == 1)
		stack->tail = NULL;
	elem = list_popfront(&stack->head);
	stack->size--;
	return (elem);
}

void	stack_pushback(t_stack *stack, t_list *elem)
{
	list_pushback(&stack->head, elem);
	stack->tail = elem;
	stack->size++;
}

void	stack_pushfront(t_stack *stack, t_list *elem)
{
	list_pushfront(&stack->head, elem);
	if (stack->tail == NULL)
		stack->tail = stack->head;
	stack->size++;
}

void	stack_destroy(t_stack *stack)
{
	list_clear(stack->head);
	free(stack);
}

void	stack_swap(t_stack *stack)
{
	t_list	*one;
	t_list	*two;

	one = stack_popfront(stack);
	two = stack_popfront(stack);
	stack_pushfront(stack, two);
	stack_pushfront(stack, one);
}

t_stack	*stack_init(size_t size, int *content)
{
	t_stack	*stack;
	size_t	i;

	stack = malloc(sizeof(t_stack));
	if (!stack)
		return (NULL);
	stack->size = size;
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
