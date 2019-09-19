/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strarrtostr.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbero <rbarbero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/19 09:54:47 by rbarbero          #+#    #+#             */
/*   Updated: 2019/09/19 10:40:29 by rbarbero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Add length of each substring of array plus one delimiter character
** between them.
*/

static size_t	compute_res_length(const char **array, const char *delim)
{
	size_t			length;
	unsigned int	i;

	length = 0;
	i = -1;
	while (array[++i])
	{
		length += ft_strlen(array[i]);
		if (delim && (i > 0))
			length++;
	}
	return (length);
}

/*
** Concatenate each substring in array in a new string with delimiter
** if it exists.
*/

char 			*ft_strarrtostr(const char **array, const char *delim)
{
	char			*res;
	const char		*str;
	unsigned char	i;

	res = NULL;
	i = -1;
	if (!(res = ft_strnew(compute_res_length(array, delim))))
		return (NULL);
	if (array)
	{
		while ((str = array[++i]))
		{
			if (delim && (i > 0))
				ft_strncat(res, delim, 1);
			ft_strcat(res, str);
		}
	}
	return (res);
}
