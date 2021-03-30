/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   list.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbruinem <tbruinem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/29 15:46:17 by tbruinem      #+#    #+#                 */
/*   Updated: 2021/03/30 13:24:59 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <push_swap.h>
#include <stdlib.h>

t_list	*list_popback(t_list **list)
{
	t_list	*last;
	t_list	*elem;

	last = *list;
	if (*list == NULL)
		return (NULL);
	while (last->next)
		last = last->next;
	if (*list == last)
		return (list_popfront(list));
	elem = last;
	last->prev->next = NULL;
	last = last->prev;
	elem->next = NULL;
	elem->prev = NULL;
	return (elem);
}

t_list	*list_popfront(t_list **list)
{
	t_list	*first;

	first = *list;
	if (!first)
		return (NULL);
	*list = (*list)->next;
	if (*list)
		(*list)->prev = NULL;
	first->next = NULL;
	first->prev = NULL;
	return (first);
}

void	list_pushback(t_list **list, t_list *elem)
{
	t_list	*iter;

	if (*list == NULL)
	{
		list_pushfront(list, elem);
		return ;
	}
	iter = *list;
	while (iter->next)
		iter = iter->next;
	iter->next = elem;
	elem->prev = iter;
}

void	list_pushfront(t_list **list, t_list *elem)
{
	t_list	*head;

	head = *list;
	*list = elem;
	elem->next = head;
	if (head)
		head->prev = elem;
}

void	list_clear(t_list *list)
{
	t_list	*del;

	while (list)
	{
		del = list;
		list = list->next;
		free(del);
	}
}

t_list	*list_new(int content)
{
	t_list	*list;

	list = malloc(sizeof(t_list));
	if (!list)
		return (NULL);
	list->content = content;
	list->next = NULL;
	list->prev = NULL;
	return (list);
}
