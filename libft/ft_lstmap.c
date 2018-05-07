/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbero <rbarbero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/16 16:20:23 by rbarbero          #+#    #+#             */
/*   Updated: 2018/04/04 08:29:21 by rbarbero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

t_list			*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*new;
	t_list	*node;
	t_list	*prev;
	int		is_first;

	new = NULL;
	is_first = 1;
	while (lst)
	{
		node = f(lst);
		if (node)
		{
			if (is_first)
				new = node;
			else
				prev->next = node;
			is_first = 0;
			prev = node;
		}
		lst = lst->next;
	}
	return (new);
}
