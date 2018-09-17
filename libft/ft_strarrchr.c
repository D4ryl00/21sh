/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strarrchr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbero <rbarbero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/17 16:01:14 by rbarbero          #+#    #+#             */
/*   Updated: 2018/09/17 16:29:11 by rbarbero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Return index of str if it's is in array. Else return -1.
*/

int	ft_strarrchr(char *str, char **arr)
{
	int	i;

	i = -1;
	if (arr)
	{
		while (arr[++i] && arr[i][0])
		{
			if (!ft_strcmp(arr[i], str))
				return (i);
		}
	}
	return (-1);
}
