/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbero <rbarbero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/09 19:15:56 by rbarbero          #+#    #+#             */
/*   Updated: 2017/11/13 11:26:39 by rbarbero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "libft.h"

char	*ft_strncat(char *s1, const char *s2, size_t n)
{
	int		end;
	size_t	i;

	end = -1;
	i = -1;
	while (s1[++end])
		;
	while (*s2 && ++i < n)
		s1[end++] = *s2++;
	s1[end] = '\0';
	return (s1);
}
