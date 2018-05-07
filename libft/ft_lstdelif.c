/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelif.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbero <rbarbero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/26 07:28:24 by rbarbero          #+#    #+#             */
/*   Updated: 2018/04/03 10:28:36 by rbarbero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	delete_node(t_list **list, t_list **previous, t_list **current
		, void (*del)(void *, size_t))
{
	if (*current == *list)
	{
		ft_lstdelnode(list, *current, del);
		*current = *list;
	}
	else
	{
		ft_lstdelnode(previous, *current, del);
		*current = (*previous)->next;
	}
}

void		ft_lstdelif(t_list **list, void *data
		, int (*test)(t_list *, void *), void (*del)(void *, size_t))
{
	t_list	*previous;
	t_list	*current;

	previous = NULL;
	current = *list;
	while (current)
	{
		if (test(current, data))
			delete_node(list, &previous, &current, del);
		else
		{
			previous = current;
			current = current->next;
		}
	}
}
