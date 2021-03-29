/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   list.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbruinem <tbruinem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/29 15:46:17 by tbruinem      #+#    #+#                 */
/*   Updated: 2021/03/29 18:16:08 by tbruinem      ########   odam.nl         */
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
	if ((*list)->prev == NULL)
		return (list_popfront(list));
	while (last->next)
		last = last->next;
	elem = last;
	last = last->prev;
	return (elem);
}

t_list	*list_popfront(t_list **list)
{
	t_list	*first;

	first = *list;
	*list = (*list)->next;
	if (first->next)
		first->next->prev = first->prev;
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
	(*list)->next = head;
	if (head)
		head->prev = (*list);
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
