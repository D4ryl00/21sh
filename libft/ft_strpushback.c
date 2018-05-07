/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strpushback.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbero <rbarbero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/24 10:02:48 by rbarbero          #+#    #+#             */
/*   Updated: 2018/04/24 13:54:46 by rbarbero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

size_t	ft_strpushback(char **str, char c)
{
	char	*tmp;
	size_t	len;

	len = ft_strlen(*str) + 1;
	if (!(tmp = (char *)malloc(sizeof(char) * (len + 1))))
		return (0);
	if (*str)
	{
		ft_strcpy(tmp, *str);
		free(*str);
		*str = tmp;
	}
	(*str)[len - 1] = c;
	(*str)[len] = '\0';
	return (len);
}
