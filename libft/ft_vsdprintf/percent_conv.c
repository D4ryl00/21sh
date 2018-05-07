/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   percent_conv.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbero <rbarbero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/11 11:31:45 by rbarbero          #+#    #+#             */
/*   Updated: 2018/04/01 23:45:18 by rbarbero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_vsdprintf.h"
#include "libft.h"

t_seq	*percent_conv(t_conv *conv, intmax_t n)
{
	char	*res;
	int		i;
	size_t	res_len;
	t_seq	*seq;

	res_len = *conv->width > 1 ? *conv->width : 1 + 0 * n;
	if (!(res = (char *)ft_memalloc(sizeof(char) * (res_len + 1))))
		return (NULL);
	if (conv->minus)
	{
		i = -1;
		res[++i] = '%';
		while ((size_t)++i < res_len)
			res[i] = ' ';
	}
	else
	{
		i = 0;
		while ((size_t)i < res_len - 1)
			res[i++] = conv->zero ? '0' : ' ';
		res[i] = '%';
	}
	if (!(seq = init_seq(res, res_len)))
		return (NULL);
	return (seq);
}
