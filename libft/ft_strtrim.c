/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbero <rbarbero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/13 18:26:53 by rbarbero          #+#    #+#             */
/*   Updated: 2017/11/16 21:12:17 by rbarbero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <string.h>
#include "libft.h"

char	*ft_strtrim(char const *s)
{
	char		*str;
	const char	*start;
	const char	*end;
	size_t		len;
	size_t		i;

	if (!s)
		return (NULL);
	i = 0;
	while (s[i] && (s[i] == ' ' || s[i] == '\n' || s[i] == '\t'))
		i++;
	start = &s[i];
	i = ft_strlen(s) - 1;
	while (&s[i] > start && (s[i] == ' ' || s[i] == '\n' || s[i] == '\t'))
		i--;
	end = &s[i];
	len = end - start + 1;
	if (!(str = (char *)malloc(len + 1)))
		return (NULL);
	i = 0;
	while (start <= end)
		str[i++] = *start++;
	str[i] = '\0';
	return (str);
}
