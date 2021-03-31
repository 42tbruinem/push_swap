/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   util.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbruinem <tbruinem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/31 11:17:04 by tbruinem      #+#    #+#                 */
/*   Updated: 2021/03/31 11:17:21 by tbruinem      ########   odam.nl         */
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
