/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_btreedel.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbero <rbarbero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/10 16:11:26 by rbarbero          #+#    #+#             */
/*   Updated: 2018/09/10 16:48:22 by rbarbero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

void	ft_btreedel(t_btree **abtree, void (*del)(void *, size_t))
{
	if (abtree && *abtree)
	{
		ft_btreedel(&((*abtree)->right), del);
		ft_btreedel(&((*abtree)->left), del);
		ft_btreedelone(abtree, del);
	}
}
