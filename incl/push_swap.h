/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   push_swap.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbruinem <tbruinem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/29 15:39:56 by tbruinem      #+#    #+#                 */
/*   Updated: 2021/04/02 20:17:44 by tbruinem      ########   odam.nl         */
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
typedef struct s_memory t_memory;

typedef void (*t_operation)(t_memory *memory);

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
	size_t		capacity;
}				t_lstack;

typedef struct	s_astack
{
	int			*data;
	size_t		start;
	size_t		end;
	size_t		capacity;
	int			incr;
	size_t		size;
}				t_astack;

struct	s_memory
{
	void		*a;
	void		*b;
	t_operation	*operations;
};

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

/*
**		LIST
*/

t_list	*list_popback(t_list **list);
t_list	*list_popfront(t_list **list);
void	list_pushback(t_list **list, t_list *elem);
void	list_pushfront(t_list **list, t_list *elem);
t_list	*list_new(int content);
void	list_clear(t_list *list);

enum	e_stackop
{
	PUSH,
	ROTATE,
	SWAP,
};

/*
**		LIST_STACK
*/

t_lstack	*lstack_init(size_t capacity, int *content, bool a);
void		lstack_pushfront(t_lstack *stack, t_list *elem);
void		lstack_pushback(t_lstack *stack, t_list *elem);
t_list		*lstack_popfront(t_lstack *stack);
t_list		*lstack_popback(t_lstack *stack);
void 		lstack_swap(t_lstack *stack);
void		lstack_destroy(t_lstack *stack);
void		lstack_print(char *title, size_t title_size, t_lstack *stack);
bool		lstack_check(t_lstack *stack);

void	lstack_sa(t_memory *memory);
void	lstack_sb(t_memory *memory);
void	lstack_ss(t_memory *memory);
void 	lstack_pa(t_memory *memory);
void	lstack_pb(t_memory *memory);
void	lstack_ra(t_memory *memory);
void	lstack_rb(t_memory *memory);
void	lstack_rr(t_memory *memory);
void	lstack_rra(t_memory *memory);
void	lstack_rrb(t_memory *memory);
void	lstack_rrr(t_memory *memory);

t_operation *lstack_operations();

/*
**		ARRAY_STACK
*/

void		astack_push(t_astack *from, t_astack *to);
void		astack_swap(t_astack *stack);
void		astack_rotate(t_astack *stack, int increment);
void		astack_print(char *title, size_t title_size, t_astack *stack);
t_astack	*astack_init(size_t size, int *content, bool a);
void		astack_destroy(t_astack *stack);

void	astack_sa(t_memory *memory);
void	astack_sb(t_memory *memory);
void	astack_ss(t_memory *memory);
void	astack_pa(t_memory *memory);
void	astack_pb(t_memory *memory);
void	astack_ra(t_memory *memory);
void	astack_rb(t_memory *memory);
void	astack_rr(t_memory *memory);
void	astack_rra(t_memory *memory);
void	astack_rrb(t_memory *memory);
void	astack_rrr(t_memory *memory);

t_operation *astack_operations();

/*
**		MEMORY
*/

void	memory_perform_operation(t_memory *memory, char *operation);
void	memory_destroy(t_memory *memory);
void	memory_print(t_memory *memory);
int		memory_init(t_memory *memory, int *content, size_t size);
bool	memory_check(t_memory *memory);

/*
**		PARSING
*/

int		*parse_input(size_t *size, int argc, char **argv);

/*
**		UTILS
*/

bool	util_chrset(char c, char *set);
bool	util_strset(char *str, char *set);
char	*util_strdtok(char *str, char *delimiter);
int		util_atoi(char *str);
size_t	util_strlen(char *str);
void	*util_memcpy(void *dest, void *src, size_t size);
void	*util_memdup(void *src, size_t size);
size_t	util_cap(size_t old, int incr, size_t cap);
void	util_putnum(int num);

#endif
