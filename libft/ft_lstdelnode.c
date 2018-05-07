/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelnode.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbero <rbarbero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/20 15:47:17 by rbarbero          #+#    #+#             */
/*   Updated: 2018/01/04 14:42:02 by rbarbero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdelnode(t_list **previous, t_list *node
		, void (*del)(void *, size_t))
{
	t_list	*next;

	if (previous && *previous && node)
	{
		next = node->next;
		if ((*previous)->next == node)
			(*previous)->next = next;
		else
			*previous = next;
		ft_lstdelone(&node, del);
	}
}
