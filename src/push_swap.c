/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   push_swap.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbruinem <tbruinem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/29 15:39:04 by tbruinem      #+#    #+#                 */
/*   Updated: 2021/03/30 00:32:48 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <push_swap.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

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
		i++;
	}
	*size = (size_t)(argc - 1);
	return (numbers);
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
	memory_print(&memory);
	memory_destroy(&memory);
	return (0);
}
