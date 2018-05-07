/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsortedinsert.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbero <rbarbero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/22 13:40:27 by rbarbero          #+#    #+#             */
/*   Updated: 2018/03/22 13:40:32 by rbarbero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstsortedinsert(t_list **list, t_list *node
		, int (*cmp)(t_list *, t_list *))
{
	t_list	*back;
	t_list	*current;

	if (!list)
		return (NULL);
	if (!*list)
		return ((*list = node));
	back = NULL;
	current = *list;
	while (current)
	{
		if (cmp(node, current) <= 0)
		{
			if (!back)
				*list = node;
			else
				back->next = node;
			node->next = current;
			return (node);
		}
		back = current;
		current = current->next;
	}
	back->next = node;
	return (node);
}
