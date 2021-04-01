/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   push_swap.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbruinem <tbruinem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/29 15:39:56 by tbruinem      #+#    #+#                 */
/*   Updated: 2021/04/01 13:31:50 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

#include <stddef.h>
#include <unistd.h>
#include <stdbool.h>

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 256
#endif

#define ERR_MEMFAIL		"Error: malloc failed.\n"
#define ERR_INVALID_ARG	"Error: invalid argument provided.\n"
#define ERR_INVALID_OP	"Error: invalid operation requested.\n"

int	error(char *errstr, size_t errstr_size, int exit_status);

/*
**		STRUCTS
*/

typedef struct s_list t_list;

struct s_list
{
	t_list	*next;
	t_list	*prev;
	int		content;
};

typedef struct  s_lstack
{
	t_list		*head;
	t_list		*tail;
	size_t		size;
}				t_lstack;

typedef struct	s_astack
{
	int			*data;
	size_t		start;
	size_t		end;
	size_t		size;
	int			incr;
}				t_astack;

typedef struct	s_memory
{
	t_lstack		*a;
	t_lstack		*b;
}				t_memory;

/*
**		OPERATIONS
*/

typedef void (*t_operation)(t_memory *memory);

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

/*
**		LIST
*/

t_list	*list_popback(t_list **list);
t_list	*list_popfront(t_list **list);
void	list_pushback(t_list **list, t_list *elem);
void	list_pushfront(t_list **list, t_list *elem);
t_list	*list_new(int content);
void	list_clear(t_list *list);

/*
**		LIST_STACK
*/

t_lstack	*stack_init(size_t size, int *content);
void	stack_pushfront(t_lstack *stack, t_list *elem);
void	stack_pushback(t_lstack *stack, t_list *elem);
t_list	*stack_popfront(t_lstack *stack);
t_list	*stack_popback(t_lstack *stack);
void 	stack_swap(t_lstack *stack);
void	stack_destroy(t_lstack *stack);
void	stack_print(char *title, size_t title_size, t_lstack *stack);

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

/*
**		MEMORY
*/

void	memory_perform_operation(t_memory *memory, char *operation);
void	memory_destroy(t_memory *memory);
void	memory_print(t_memory *memory);
int		memory_init(t_memory *memory, int *content, size_t size);

/*
**		PARSING
*/

int		*parse_input(size_t *size, int argc, char **argv);

/*
**		UTILS
*/

bool	chrset(char c, char *set);
bool	strset(char *str, char *set);
char	*util_strdtok(char *str, char *delimiter);
int		util_atoi(char *str);
size_t	util_strlen(char *str);

#endif
