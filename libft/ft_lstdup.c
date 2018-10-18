/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbero <rbarbero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/18 16:07:15 by rbarbero          #+#    #+#             */
/*   Updated: 2018/10/18 17:05:48 by rbarbero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static void	del(void *content, size_t size)
{
	(void)size;
	free(content);
}

t_list		*ft_lstdup(t_list *src)
{
	t_list	*dest;
	t_list	*save;

	dest = NULL;
	if (src)
	{
		if (!(save = ft_lstnewnode(&dest, src->content, src->content_size)))
			return (NULL);
		src = src->next;
		while (src)
		{
			if (!ft_lstnewnode(&dest, src->content, src->content_size))
			{
				ft_lstdel(&save, del);
				return (NULL);
			}
			dest = dest->next;
			src = src->next;
		}
		dest = save;
	}
	return (dest);
}
