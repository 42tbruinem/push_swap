/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   util.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbruinem <tbruinem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/31 11:17:04 by tbruinem      #+#    #+#                 */
/*   Updated: 2021/03/31 12:14:23 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <push_swap.h>
#include <stdbool.h>

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

size_t	util_strlen(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}
