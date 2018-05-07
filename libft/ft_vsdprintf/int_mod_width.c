/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   int_mod_width.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbero <rbarbero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/09 18:50:38 by rbarbero          #+#    #+#             */
/*   Updated: 2018/04/01 23:43:54 by rbarbero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_vsdprintf.h"
#include "libft.h"
#include <stdlib.h>

static void	mod_width_aux(char *res, char **str, size_t str_len, t_conv *conv)
{
	UCHAR	i;

	i = -1;
	if (conv->zero && (**str == '+' || **str == '-' || **str == ' '))
	{
		res[++i] = **str;
		while (++i < *conv->width - str_len + 1)
			res[i] = '0';
		ft_strcat(res, &((*str)[1]));
	}
	else
	{
		while (++i < *conv->width - str_len)
			res[i] = conv->zero ? '0' : ' ';
		ft_strcat(res, *str);
	}
}

char		*int_mod_width(char **str, t_conv *conv)
{
	char	*res;
	size_t	str_len;
	UCHAR	i;

	str_len = ft_strlen(*str);
	conv->minus = *conv->width < 0 ? 1 : conv->minus;
	*conv->width = ft_absolute(*conv->width);
	if (str_len < (size_t)*conv->width)
	{
		if (!(res = (char *)ft_memalloc(sizeof(char) * (*conv->width + 1))))
			return (NULL);
		if (!conv->minus)
			mod_width_aux(res, str, str_len, conv);
		else
		{
			i = str_len - 1;
			ft_strcat(res, *str);
			while (++i < *conv->width)
				res[i] = ' ';
		}
		free(*str);
		*str = res;
	}
	return (*str);
}
