/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strarrdel.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbero <rbarbero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/15 22:24:59 by rbarbero          #+#    #+#             */
/*   Updated: 2018/09/15 23:20:01 by rbarbero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

/*
** Free a array of string finished by a NULL pointer.
*/
void	ft_strarrdel(char **arr)
{
	char	**p;
	if (arr)
	{
		p = arr;
		while (p)
		{
			if (*p)
				free(*p);
			p++;
		}
		free(arr);
	}
}
