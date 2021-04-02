/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   util.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbruinem <tbruinem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/31 11:17:04 by tbruinem      #+#    #+#                 */
/*   Updated: 2021/04/02 19:18:33 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <push_swap.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>

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

void		util_putnum(int num)
{
	char	c;

	if (num >= 10)
		util_putnum(num / 10);
	c = (num % 10) + '0';
	write(1, &c, 1);
}

size_t		util_cap(size_t old, int incr, size_t cap)
{
	if (!incr)
		return (old);
	else if (incr > 0)
		return ((old + incr) % cap);
	else if ((size_t)(incr * -1) > old)
		return (cap - ((incr * -1) - old));
	return (old - incr);
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

void	*util_memcpy(void *dest, void *src, size_t size)
{
	size_t	i;

	i = 0;
	while (i < size)
	{
		((unsigned char*)dest)[i] = ((unsigned char*)src)[i];
		i++;
	}
	return (dest);
}

void	*util_memdup(void *src, size_t size)
{
	void	*mem;

	mem = malloc(size);
	if (!mem)
		return (NULL);
	util_memcpy(mem, src, size);
	return (mem);
}

size_t	util_strlen(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}
