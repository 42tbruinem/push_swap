/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   stack.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbruinem <tbruinem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/29 15:42:20 by tbruinem      #+#    #+#                 */
/*   Updated: 2021/03/29 18:12:16 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <push_swap.h>

#include <stdlib.h>

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
	if (stack->size)
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
	i = 0;
	stack->head = NULL;
	stack->tail = NULL;
	while (i < size)
	{
		stack_pushfront(stack, list_new(content[i]));
		i++;
	}
	return (stack);
}
