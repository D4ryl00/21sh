/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbero <rbarbero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/09 20:21:04 by rbarbero          #+#    #+#             */
/*   Updated: 2017/11/09 21:05:33 by rbarbero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

char	*ft_strstr(const char *haystack, const char *needle)
{
	int	i;
	int	found;

	if (!*needle)
		return ((char *)haystack);
	i = -1;
	while (haystack[++i])
	{
		found = 0;
		while (haystack[i + found] == needle[found] || !needle[found])
		{
			if (!needle[found])
				return ((char *)&haystack[i]);
			found++;
		}
	}
	return (NULL);
}
