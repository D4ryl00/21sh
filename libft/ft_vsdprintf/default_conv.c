/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   default_conv.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbero <rbarbero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/18 19:49:47 by rbarbero          #+#    #+#             */
/*   Updated: 2018/04/01 23:40:43 by rbarbero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_vsdprintf.h"
#include "libft.h"

static void	default_conv_aux(char *res, size_t res_len, t_conv *conv)
{
	UCHAR	i;

	if (conv->minus)
	{
		i = -1;
		res[++i] = *(char *)conv->data;
		while ((size_t)++i < res_len)
			res[i] = ' ';
	}
	else
	{
		i = 0;
		while ((size_t)i < res_len - 1)
			res[i++] = conv->zero ? '0' : ' ';
		res[i] = *(char *)conv->data;
	}
}

t_seq		*default_conv(t_conv *conv, intmax_t n)
{
	char	*res;
	size_t	res_len;
	t_seq	*seq;

	(void)n;
	if (*(char *)conv->data)
	{
		res_len = *conv->width > 1 ? *conv->width : 1;
		if (!(res = (char *)ft_memalloc(sizeof(char) * (res_len + 1))))
			return (NULL);
		default_conv_aux(res, res_len, conv);
		if (!(seq = init_seq(res, res_len)))
			return (NULL);
	}
	else if (!(seq = init_seq(NULL, 0)))
		return (NULL);
	return (seq);
}
