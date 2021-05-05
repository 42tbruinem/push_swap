/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lstack.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbruinem <tbruinem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/29 15:42:20 by tbruinem      #+#    #+#                 */
/*   Updated: 2021/04/02 20:18:01 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <push_swap.h>

#include <stdlib.h>
#include <stdio.h>
#include <limits.h>

void	lstack_print(char *title, size_t title_size, t_lstack *stack)
{
	size_t	i;
	t_list	*begin;

	i = 0;
	begin = stack->head;
	write(1, title, title_size);
	while (begin)
	{
		util_putnum(begin->content);
		if (begin->next)
			write(1, " -> ", 4);
		i++;
		begin = begin->next;
	}
	write(1, "\n", 1);
}

t_list	*lstack_popback(t_lstack *stack)
{
	t_list	*elem;

	if (!stack->capacity)
		return (NULL);
	if (stack->tail)
		stack->tail = stack->tail->prev;
	elem = list_popback(&stack->head);
	stack->capacity--;
	return (elem);
}

t_list	*lstack_popfront(t_lstack *stack)
{
	t_list	*elem;

	if (!stack->capacity)
		return (NULL);
	if (stack->capacity == 1)
		stack->tail = NULL;
	elem = list_popfront(&stack->head);
	stack->capacity--;
	return (elem);
}

void	lstack_pushback(t_lstack *stack, t_list *elem)
{
	if (!elem)
		exit(error(ERR_MEMFAIL, sizeof(ERR_MEMFAIL), 1));
	list_pushback(&stack->head, elem);
	stack->tail = elem;
	stack->capacity++;
}

void	lstack_pushfront(t_lstack *stack, t_list *elem)
{
	list_pushfront(&stack->head, elem);
	if (stack->tail == NULL)
		stack->tail = stack->head;
	stack->capacity++;
}

void	lstack_destroy(t_lstack *stack)
{
	list_clear(stack->head);
	free(stack);
}

void	lstack_swap(t_lstack *stack)
{
	t_list	*one;
	t_list	*two;

	if (stack->capacity < 2)
		return ;
	one = lstack_popfront(stack);
	two = lstack_popfront(stack);
	lstack_pushfront(stack, one);
	lstack_pushfront(stack, two);
}

bool	lstack_check(t_lstack *stack)
{
	t_list	*iter;
	int		last = INT_MIN;

	iter = stack->head;
	while (iter)
	{
		if (iter->content < last)
			return (false);
		last = iter->content;
		iter = iter->next;
	}
	return (true);
}

t_lstack	*lstack_init(size_t capacity, int *content, bool a)
{
	t_lstack	*stack;
	size_t	i;

	stack = malloc(sizeof(t_lstack));
	if (!stack)
		return (NULL);
	stack->capacity = 0;
	stack->head = NULL;
	stack->tail = NULL;
	i = 0;
	while (i < capacity && a)
	{
		lstack_pushback(stack, list_new(content[i]));
		i++;
	}
	return (stack);
}

/*
**		OPERATIONS
*/

void	lstack_sa(t_memory *memory)
{
	lstack_swap(memory->a);
}
void	lstack_sb(t_memory *memory)
{
	lstack_swap(memory->b);
}
void	lstack_ss(t_memory *memory)
{
	lstack_sa(memory);
	lstack_sb(memory);
}
void 	lstack_pa(t_memory *memory)
{
	t_list		*top_of_b;
	t_lstack	*stack;

	stack = memory->b;
	if (stack->capacity < 1)
		return ;
	top_of_b = lstack_popfront(memory->b);
	if (!top_of_b)
		return ;
	lstack_pushfront(memory->a, top_of_b);
}
void	lstack_pb(t_memory *memory)
{
	t_list		*top_of_a;
	t_lstack	*stack;

	stack = memory->a;
	if (stack->capacity < 1)
		return ;
	top_of_a = lstack_popfront(memory->a);
	if (!top_of_a)
		return ;
	lstack_pushfront(memory->b, top_of_a);
}
void	lstack_ra(t_memory *memory)
{
	t_list	*old_top;
	t_lstack	*stack;

	stack = memory->a;
	if (stack->capacity < 2)
		return ;
	old_top = lstack_popfront(memory->a);
	lstack_pushback(memory->a, old_top);
}
void	lstack_rb(t_memory *memory)
{
	t_list		*old_top;
	t_lstack	*stack;

	stack = memory->b;
	if (stack->capacity < 2)
		return ;
	old_top = lstack_popfront(memory->b);
	lstack_pushback(memory->b, old_top);
}
void	lstack_rr(t_memory *memory)
{
	lstack_ra(memory);
	lstack_rb(memory);
}
void	lstack_rra(t_memory *memory)
{
	t_list		*old_bottom;
	t_lstack	*stack;

	stack = memory->a;
	if (stack->capacity < 2)
		return ;
	old_bottom = lstack_popback(memory->a);
	lstack_pushfront(memory->a, old_bottom);
}
void	lstack_rrb(t_memory *memory)
{
	t_list		*old_bottom;
	t_lstack	*stack;

	stack = memory->b;
	if (stack->capacity < 2)
		return ;
	old_bottom = lstack_popback(memory->b);
	lstack_pushfront(memory->b, old_bottom);
}
void	lstack_rrr(t_memory *memory)
{
	lstack_rra(memory);
	lstack_rrb(memory);
}

t_operation	*lstack_operations(void)
{
	static t_operation		operations[] = {
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
	return (operations);
}
