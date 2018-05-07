/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnewnode.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbero <rbarbero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/17 14:31:35 by rbarbero          #+#    #+#             */
/*   Updated: 2017/11/17 15:16:19 by rbarbero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "libft.h"

/*
** This function create a new node after the existing in the pointer in lst.
** If there is no list in the pointer in lst, this pointer will point on the
** new node.
*/

t_list	*ft_lstnewnode(t_list **lst, void *content, size_t content_size)
{
	if (!lst)
		return (NULL);
	if (!*lst)
		return (*lst = ft_lstnew(content, content_size));
	return ((*lst)->next = ft_lstnew(content, content_size));
}
