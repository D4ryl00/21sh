/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstpushback.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbero <rbarbero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/20 10:29:41 by rbarbero          #+#    #+#             */
/*   Updated: 2018/01/04 14:35:01 by rbarbero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstpushback(t_list **begin_list, void *content, size_t content_size)
{
	t_list	*tmp;

	if (begin_list)
	{
		tmp = *begin_list;
		if (*begin_list)
		{
			while (tmp->next)
				tmp = tmp->next;
			return ((tmp->next = ft_lstnew(content, content_size)));
		}
		else
			return ((*begin_list = ft_lstnew(content, content_size)));
	}
	return (0);
}
