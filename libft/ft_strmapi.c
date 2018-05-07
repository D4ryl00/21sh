/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbero <rbarbero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/13 17:19:12 by rbarbero          #+#    #+#             */
/*   Updated: 2017/11/16 21:06:13 by rbarbero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <string.h>
#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*str;
	size_t	len;
	size_t	i;

	if (s)
	{
		len = ft_strlen(s);
		if (!(str = (char *)malloc(len + 1)))
			return (NULL);
		i = -1;
		while (++i < len)
			str[i] = f(i, s[i]);
		str[i] = '\0';
		return (str);
	}
	return (NULL);
}
