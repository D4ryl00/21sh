/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstselect.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbero <rbarbero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/03 11:13:47 by rbarbero          #+#    #+#             */
/*   Updated: 2018/04/03 11:25:13 by rbarbero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstselect(t_list *list, void *data, int (*test)(t_list *, void *))
{
	while (list)
	{
		if (test(list, data))
			return (list);
		list = list->next;
	}
	return (NULL);
}
