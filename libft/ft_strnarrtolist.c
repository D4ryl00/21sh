/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnarrtolist.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbero <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/10 10:21:20 by rbarbero          #+#    #+#             */
/*   Updated: 2018/10/18 16:01:11 by rbarbero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static void	del_node(void *content, size_t size)
{
	(void)size;
	free(content);
}

t_list		*ft_strnarrtolist(char **arr, int len)
{
	int		i;
	t_list	*list;
	t_list	*next;

	i = len;
	list = NULL;
	next = NULL;
	while (--i > 0)
	{
		if (list)
			next = list;
		if (!(list = ft_lstnew(arr[i], ft_strlen(arr[i]) + 1)))
		{
			ft_lstdel(&next, del_node);
			return (NULL);
		}
		list->next = next;
	}
	return (list);
}
