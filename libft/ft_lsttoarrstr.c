/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lsttoarrstr.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbero <rbarbero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/16 22:40:41 by rbarbero          #+#    #+#             */
/*   Updated: 2018/09/16 22:48:50 by rbarbero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	**ft_lsttoarrstr(t_list *lst)
{
	char	**dest;
	int		i;

	dest = NULL;
	if (!(dest = (char **)malloc(sizeof(char *) * ft_lstsize(lst) + 1)))
	{
		i = 0;
		while (lst)
		{
			if (!(dest[i++] = ft_strdup(lst->content)))
			{
				ft_strarrdel(dest);
				return (NULL);
			}
			lst = lst->next;
		}
		dest[i] = NULL;
	}
	return (dest);
}
