/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   checker.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbruinem <tbruinem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/31 11:12:40 by tbruinem      #+#    #+#                 */
/*   Updated: 2021/03/31 13:55:16 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <push_swap.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

char	*run_operations(t_memory *memory, char *buffer)
{
	char	*tok;
	char	*oldtok;

	(void)memory;
	tok = util_strdtok(buffer, "\n");
	while (tok)
	{
		printf("%s\n", tok);
		oldtok = tok;
		tok = util_strdtok(NULL, "\n");
	}
	return (oldtok);
}

size_t	get_remainder(char *buffer, char *last_token)
{
	

}

void	read_buffer(t_memory *memory)
{
	char	buffer[BUFFER_SIZE + 1];
	char	*last_token;
	int		ret;
	size_t	remainder;

	remainder = 0;
	(void)memory;
	ret = 1;
	while (ret >= 0)
	{
		ret = read(STDIN_FILENO, buffer, BUFFER_SIZE);
		if (!ret)
			break ;
		buffer[ret] = '\0';
		last_token = run_operations(memory, buffer);
		(void)last_token;
		printf("---\n");
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
	read_buffer(&memory);
	return (0);
}
