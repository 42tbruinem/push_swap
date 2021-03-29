/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   push_swap.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbruinem <tbruinem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/29 15:39:56 by tbruinem      #+#    #+#                 */
/*   Updated: 2021/03/29 17:05:39 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

#include <stddef.h>

typedef struct s_list t_list;

struct s_list
{
    t_list  *next;
	t_list	*prev;
    void    *content;
};

typedef struct  s_stack
{
    t_list      *head;
	t_list		*tail;
    size_t		size;
}               t_stack;

typedef struct	s_memory
{
	t_stack		*a;
	t_stack		*b;
}				t_memory;

/*
**		LIST
*/

t_list	*list_popback(t_list **list);
t_list	*list_popfront(t_list **list);
void	list_pushback(t_list **list, t_list *elem);
void	list_pushfront(t_list **list, t_list *elem);
t_list	*list_new(int content);

/*
**		STACK
*/

t_stack	*stack_init(size_t size, int *content);
void	stack_pushfront(t_stack *stack, t_list *elem);
void	stack_pushback(t_stack *stack, t_list *elem);
t_list	*stack_popfront(t_stack *stack);
t_list	*stack_popback(t_stack *stack);
void 	stack_swap(t_stack *stack);

/*
**		OPERATIONS
*/

enum	e_op
{
	OP_SA,
	OP_SB,
	OP_SS,
	OP_PA,
	OP_PB,
	OP_RA,
	OP_RB,
	OP_RR,
	OP_RRA,
	OP_RRB,
	OP_RRR
};

int		memory_init(t_memory *memory);

typedef void (*t_operation)(t_memory *memory);

void	sa(t_memory *memory);
void	sb(t_memory *memory);
void	ss(t_memory *memory);
void 	pa(t_memory *memory);
void	pb(t_memory *memory);
void	ra(t_memory *memory);
void	rb(t_memory *memory);
void	rr(t_memory *memory);
void	rra(t_memory *memory);
void	rrb(t_memory *memory);
void	rrr(t_memory *memory);

#endif
