/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   char_conv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbero <rbarbero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/22 10:01:05 by rbarbero          #+#    #+#             */
/*   Updated: 2018/04/01 23:40:21 by rbarbero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_vsdprintf.h"
#include "libft.h"
#include <wchar.h>
#include <stdlib.h>

static t_seq	*conv_arg(t_seq *seq, t_conv *conv)
{
	char	*res;

	if (conv->modifier[0] == 'l')
	{
		if (!(res = (char *)ft_memalloc(MB_CUR_MAX)))
			return (NULL);
		if (!ft_is_valid_unicode(*(wint_t *)conv->data)
				|| !(seq->len = ft_wctomb(res, *(wint_t *)conv->data)))
		{
			free(res);
			return (NULL);
		}
	}
	else
	{
		if (!(res = (char *)ft_memalloc(sizeof(unsigned char))))
			return (NULL);
		res[0] = *(int *)conv->data;
		seq->len = sizeof(unsigned char);
	}
	seq->str = res;
	return (seq);
}

static void		char_mod_width_aux(char *res, t_seq *seq, t_conv *conv)
{
	UCHAR	i;

	if (conv->minus)
	{
		ft_memcpy(res, seq->str, seq->len);
		i = seq->len;
		while (i < *conv->width)
			res[i++] = ' ';
	}
	else
	{
		i = -1;
		while (++i < *conv->width - seq->len)
			res[i] = conv->zero ? '0' : ' ';
		ft_memcpy(&res[i], seq->str, seq->len);
	}
}

static t_seq	*char_mod_width(t_seq *seq, t_conv *conv)
{
	char	*res;

	conv->minus = *conv->width < 0 ? 1 : conv->minus;
	*conv->width = ft_absolute(*conv->width);
	if ((int)(*conv->width - seq->len) >= 1)
	{
		if (!(res = (char *)ft_memalloc(sizeof(char) * (*conv->width))))
			return (NULL);
		char_mod_width_aux(res, seq, conv);
		free(seq->str);
		seq->str = res;
		seq->len = *conv->width;
	}
	return (seq);
}

t_seq			*char_conv(t_conv *conv, intmax_t n)
{
	t_seq	*seq;

	(void)n;
	if (!(seq = init_seq(NULL, 0)))
		return (NULL);
	if (!conv_arg(seq, conv) || !char_mod_width(seq, conv))
	{
		free(seq);
		return (NULL);
	}
	return (seq);
}
