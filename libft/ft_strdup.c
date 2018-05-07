/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbero <rbarbero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/09 18:14:14 by rbarbero          #+#    #+#             */
/*   Updated: 2017/11/10 14:29:24 by rbarbero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <stdlib.h>
#include "libft.h"

char			*ft_strdup(const char *s1)
{
	char	*dst;
	size_t	size;

	size = ft_strlen(s1);
	if (!(dst = (char *)malloc(sizeof(char) * (size + 1))))
		return (NULL);
	ft_strcpy(dst, s1);
	return (dst);
}
