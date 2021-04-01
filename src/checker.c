/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   checker.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbruinem <tbruinem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/31 11:12:40 by tbruinem      #+#    #+#                 */
/*   Updated: 2021/04/01 21:32:18 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <push_swap.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

char	*run_operations(t_memory *memory, char *buffer, int ret)
{
	char	*tok;
	char	*oldtok;

	(void)memory;
	tok = buffer;
	oldtok = tok;
	if (ret)
		tok = util_strdtok(buffer, "\n");
	while (tok)
	{
		printf("%s\n", tok);
		memory_perform_operation(memory, tok);
		memory_print(memory);
		oldtok = tok;
		tok = util_strdtok(NULL, "\n");
	}
	return (oldtok);
}

size_t	get_remainder(char *buffer, char *last_token)
{
	size_t	i;

	i = 0;
	if (!last_token)
		return (0);
	while (*last_token && last_token < buffer + BUFFER_SIZE)
		last_token++;
	while (!*last_token && last_token < buffer + BUFFER_SIZE)
		last_token++;
	while (last_token + i < buffer + BUFFER_SIZE && last_token[i])
	{
		buffer[i] = last_token[i];
		i++;
	}
	return (i);
}

void	read_buffer(t_memory *memory)
{
	char	buffer[BUFFER_SIZE + 1];
	char	*last_token;
	int		ret;
	size_t	remainder;

	remainder = 0;
	ret = 1;
	while (ret >= 0)
	{
		ret = read(STDIN_FILENO, buffer + remainder, BUFFER_SIZE - remainder);
		buffer[remainder + ret] = '\0';
		last_token = run_operations(memory, buffer, ret);
		if (!ret)
			break ;
		if (last_token == buffer)
			remainder = (ret + remainder);
		else
			remainder = get_remainder(buffer, last_token);
	}
}

int	main(int argc, char **argv)
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
	read_buffer(&memory);
	if (memory_check(&memory))
		write(1, "OK", 2);
	else
		write(1, "KO", 2);
	memory_destroy(&memory);
	write(1, "\n", 1);
	return (0);
}
