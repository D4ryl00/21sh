/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbero <rbarbero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/10 13:53:14 by rbarbero          #+#    #+#             */
/*   Updated: 2017/11/16 20:48:55 by rbarbero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	found;

	if (!*needle)
		return ((char *)haystack);
	i = 0;
	while (i < len && haystack[i])
	{
		found = 0;
		while (i + found < len && haystack[i + found] && needle[found]
				&& haystack[i + found] == needle[found])
			found++;
		if (!needle[found])
			return ((char *)&haystack[i]);
		i++;
	}
	return (NULL);
}
