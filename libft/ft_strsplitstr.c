/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_whitespaces.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbero <rbarbero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/21 18:06:44 by rbarbero          #+#    #+#             */
/*   Updated: 2018/04/24 14:19:43 by rbarbero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static int	get_str_nbr(char const *str, char *tokens)
{
	int				len;
	unsigned char	f_word;

	len = 0;
	f_word = 0;
	if (tokens)
	{
		while (*str)
		{
			if (ft_strchr(tokens, *str) && f_word)
			{
				f_word = 0;
				len++;
			}
			else
				f_word = 1;
			str++;
		}
		if (f_word)
			len++;
	}
	return (len);
}

static char	**free_dest(char **dest, int str_nbr)
{
	int	i;

	i = -1;
	while (++i < str_nbr)
	{
		if (dest[i])
			free(dest[i]);
	}
	return (NULL);
}

static char	**fill_dest(char **dest, char const *str, int str_nbr, char *tokens)
{
	char const	*end;
	int			i;

	i = -1;
	while (*str)
	{
		while (*str && ft_strchr(tokens, *str))
			str++;
		end = str;
		while (*end && !ft_strchr(tokens, *end))
			end++;
		if (end != str)
		{
			if (!(dest[++i] = (char *)ft_memalloc(sizeof(char)
							* (end - str + 1))))
				return (free_dest(dest, str_nbr));
			ft_strncpy(dest[i], str, end - str);
		}
		str = end;
	}
	return (dest);
}

char		**ft_strsplitstr(char const *str, char *tokens)
{
	int		str_nbr;
	char	**dest;
	int		i;

	if (!str)
		str_nbr = 0;
	else
		str_nbr = get_str_nbr(str, tokens);
	if (!(dest = (char **)malloc(sizeof(char *) * (str_nbr + 1))))
		return (NULL);
	i = -1;
	while (++i < str_nbr + 1)
		dest[i] = NULL;
	if (!str)
		return (dest);
	else
		return (fill_dest(dest, str, str_nbr, tokens));
}
