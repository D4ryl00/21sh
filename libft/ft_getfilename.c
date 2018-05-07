/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getfilename.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbero <rbarbero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/23 13:52:16 by rbarbero          #+#    #+#             */
/*   Updated: 2018/03/23 14:05:54 by rbarbero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_getfilename(char *path)
{
	char	*start;

	if (!path)
		return (NULL);
	start = path;
	while (*start)
		start++;
	start--;
	while (*start && *start != '/')
		start--;
	return (ft_strdup(++start));
}
