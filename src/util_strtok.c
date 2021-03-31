/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   util_strtok.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbruinem <tbruinem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/31 11:20:05 by tbruinem      #+#    #+#                 */
/*   Updated: 2021/03/31 11:57:48 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <push_swap.h>
#include <stdio.h>

char	*util_strtok(char *str, char *delimiter)
{
	static char	*buffer = NULL;

	if (str != NULL)
		buffer = str;
	if (!str && (!buffer || !*buffer))
		return (NULL);
	while (chrset(*buffer, delimiter))
		buffer++;
	str = buffer;
	while (*buffer && !chrset(*buffer, delimiter))
		buffer++;
	while (chrset(*buffer, delimiter))
	{
		*buffer = '\0';
		buffer++;
	}
	return (str);
}
