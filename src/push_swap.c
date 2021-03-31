/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   push_swap.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbruinem <tbruinem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/29 15:39:04 by tbruinem      #+#    #+#                 */
/*   Updated: 2021/03/31 11:13:42 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <push_swap.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

size_t	util_strlen(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

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

bool	chrset(char c, char *set)
{
	size_t	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (true);
		i++;
	}
	return (false);
}

bool	strset(char *str, char *set)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		if (!chrset(str[i], set))
			return (false);
		i++;
	}
	return (true);
}


bool	duplicate(int number, int *content, size_t size)
{
	size_t	i;

	i = 0;
	while (i < size)
	{
		if (number == content[i])
			return (true);
		i++;
	}
	return (false);
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
		if (!strset(argv[i], "0123456789-"))
			exit(error(ERR_INVALID_ARG, sizeof(ERR_INVALID_ARG), 1));
		numbers[i - 1] = util_atoi(argv[i]);
		if (duplicate(numbers[i - 1], numbers, i - 1))
			exit(error(ERR_INVALID_ARG, sizeof(ERR_INVALID_ARG), 1));
		i++;
	}
	*size = (size_t)(argc - 1);
	return (numbers);
}

void	perform_op(t_memory *memory, char *operation)
{
	size_t	operation_length;

	operation_length = (!operation) ? 0 : util_strlen(operation);

	printf("      %s      \n", operation);
	printf("------");
	for (size_t i = 0; i < operation_length; i++)
		printf("%c", '-');
	printf("------\n");
	if (operation)
		memory_perform_operation(memory, operation);
	memory_print(memory);
	printf("------");
	for (size_t i = 0; i < operation_length; i++)
		printf("%c", '-');
	printf("------\n");
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
	free(content);
	perform_op(&memory, NULL);
	perform_op(&memory, "rb");
	perform_op(&memory, "ra");
	perform_op(&memory, "sa");
	perform_op(&memory, "pb");
	perform_op(&memory, "pa");
	perform_op(&memory, "pb");
	perform_op(&memory, "pb");
	perform_op(&memory, "pb");
	perform_op(&memory, "rb");
	perform_op(&memory, "sb");
	perform_op(&memory, "rra");
	memory_destroy(&memory);
	return (0);
}
