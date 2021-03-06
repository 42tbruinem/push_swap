/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_input.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbruinem <tbruinem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/31 12:13:37 by tbruinem      #+#    #+#                 */
/*   Updated: 2021/03/31 12:23:28 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <push_swap.h>
#include <stdlib.h>

static bool	duplicate(int number, int *content, size_t size)
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
