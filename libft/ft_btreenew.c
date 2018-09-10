/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_btreenew.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbero <rbarbero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/10 15:12:37 by rbarbero          #+#    #+#             */
/*   Updated: 2018/09/10 15:19:56 by rbarbero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

t_btree	*ft_btreenew(void const *content, size_t content_size)
{
	t_btree	*btree;

	if (!(btree = (t_btree *)malloc(sizeof(t_btree))))
		return (NULL);
	if (content)
	{
		if (!(btree->content = malloc(content_size)))
		{
			free(btree);
			return (NULL);
		}
		ft_memcpy(btree->content, content, content_size);
		btree->content_size = content_size;
	}
	else
	{
		btree->content = NULL;
		btree->content_size = 0;
	}
	btree->left = NULL;
	btree->right = NULL;
	return (btree);
}
