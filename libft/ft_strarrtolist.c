/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strarrtolist.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbero <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/10 10:23:41 by rbarbero          #+#    #+#             */
/*   Updated: 2018/04/10 10:27:55 by rbarbero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_strarrtolist(char **arr)
{
	int	len;

	len = 0;
	if (arr)
	{
		while (arr[len])
			len++;
	}
	return (ft_strnarrtolist(arr, len));
}
