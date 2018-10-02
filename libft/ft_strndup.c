/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbero <rbarbero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/28 02:30:58 by rbarbero          #+#    #+#             */
/*   Updated: 2018/09/28 02:42:58 by rbarbero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <string.h>
#include <stdlib.h>

/*
** Allocate enough memory and duplicate n characters of the string.
** Set a zero terminal char at the end.
*/

char	*ft_strndup(const char *s1, unsigned int n)
{
	char	*dst;

	dst = NULL;
	if (s1)
	{
		if (!(dst = (char *)malloc(sizeof(char) * ((size_t)n + 1))))
			return (NULL);
		ft_strncpy(dst, s1, n);
		dst[n] = '\0';
	}
	return (dst);
}
