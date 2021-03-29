/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   push_swap.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbruinem <tbruinem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/29 15:39:04 by tbruinem      #+#    #+#                 */
/*   Updated: 2021/03/29 18:13:58 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <push_swap.h>
#include <stdlib.h>

int	util_atoi(char *str)
{
	int		sign;
	int		res;
	int		i;

	res = 0;
	sign = (str[0] == '+') - (str[0] == '-');
	i = !!sign;
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = res * 10 + (str[i] - '0');
		i++;
	}
	sign += (!sign);
	return (res * sign);
}

int	*parse_input(size_t *size, int argc, char **argv)
{
	int		*numbers;
	int		i;

	numbers = malloc(sizeof(int) * (argc - 1));
	if (!numbers)
		return (NULL);
	i = 1;
	while (i < argc)
	{
		numbers[i - 1] = util_atoi(argv[i]);
		i++;
	}
	*size = (size_t)(argc - 1);
	return (numbers);
}

void	print_stack(t_stack *stack)
{
	size_t	i;
	t_list	*begin;

	i = 0;
	begin = stack->head;
	while (i < stack->size)
	{
		write(1, &begin->content, sizeof(int));
		i++;
		begin = begin->next;
	}
	write(1, "\n", 1);
}

void	print_memory(t_memory *memory)
{
	print_stack(memory->a);
	print_stack(memory->b);
}

int main(int argc, char **argv)
{
	t_memory	memory;
	int			*content;
	size_t		size;

	if (argc == 1)
		return (error(ERR_INVALID_ARG, sizeof(ERR_INVALID_ARG), 1));
	content = parse_input(&size, argc, argv);
	if (!content || !memory_init(&memory, content, size))
		return (error(ERR_MEMFAIL, sizeof(ERR_MEMFAIL), 1));
	print_memory(&memory);
    return (0);
}
