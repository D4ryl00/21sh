/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstpush.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbero <rbarbero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/05 10:04:42 by rbarbero          #+#    #+#             */
/*   Updated: 2018/11/05 10:17:42 by rbarbero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Create a new t_list node and add it in front of the list
** (or assign the list to the node if the list was NULL)
*/

t_list	*ft_lstpush(t_list **list, void *content, size_t content_size)
{
	t_list	*node;
	t_list	*tmp;

	tmp = NULL;
	if (!list)
		return (NULL);
	if (!(node = ft_lstnew(content, content_size)))
		return (NULL);
	if (*list)
		tmp = *list;
	*list = node;
	node->next = tmp;
	return (node);
}
