/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   util_strdtok.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbruinem <tbruinem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/31 11:20:05 by tbruinem      #+#    #+#                 */
/*   Updated: 2021/04/01 21:01:06 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <push_swap.h>
#include <stdio.h>

/*
**	Str tokenize, with the added modification that a string
**	is not returned unless it's ended with atleast one delimiter
*/
char	*util_strdtok(char *str, char *delimiter)
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
	if (!chrset(*buffer, delimiter))
		return (NULL);
	while (chrset(*buffer, delimiter))
	{
		*buffer = '\0';
		buffer++;
	}
	return (str);
}
