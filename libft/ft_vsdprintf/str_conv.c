/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_conv.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbero <rbarbero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/18 09:47:01 by rbarbero          #+#    #+#             */
/*   Updated: 2018/04/01 23:45:49 by rbarbero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_vsdprintf.h"
#include "libft.h"
#include <wchar.h>
#include <stdlib.h>

static t_seq	*conv_arg_l(t_seq *seq, t_conv *conv)
{
	char	*res;
	size_t	len;
	size_t	max;
	int		byte;
	int		i;

	max = ft_wcslen(*(wchar_t **)conv->data);
	len = conv->dot && ((size_t)*conv->precision < (max * MB_CUR_MAX))
		? (size_t)*conv->precision : max * MB_CUR_MAX;
	if (!(res = (char *)ft_memalloc((len + 1))))
		return (NULL);
	i = -1;
	while ((size_t)++i < max && seq->len < len)
	{
		if (!ft_is_valid_unicode((*(wchar_t **)conv->data)[i]) || !(byte =
					ft_wctomb(&res[seq->len], (*(wchar_t **)conv->data)[i])))
		{
			free(res);
			return (NULL);
		}
		seq->len += seq->len + byte > len ? 0 : byte;
	}
	seq->str = res;
	return (seq);
}

static t_seq	*conv_arg(t_seq *seq, t_conv *conv)
{
	char	*res;
	size_t	len;

	if (!*(char **)conv->data)
	{
		seq->len = conv->dot && (size_t)*conv->precision < 6
			? *conv->precision : 6;
		if (!(res = ft_strdup("(null)")))
			return (NULL);
	}
	else if (conv->modifier[0] == 'l')
		return (conv_arg_l(seq, conv));
	else
	{
		len = ft_strlen(*((char **)conv->data));
		if (conv->dot && (size_t)*conv->precision < len)
			len = *conv->precision;
		if (!(res = (char *)ft_memalloc(sizeof(char) * (len + 1))))
			return (NULL);
		ft_strncpy(res, *((char **)conv->data), len);
		seq->len = len;
	}
	seq->str = res;
	return (seq);
}

static void		str_mod_width_aux(char *res, t_seq *seq, t_conv *conv)
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

static t_seq	*str_mod_width(t_seq *seq, t_conv *conv)
{
	char	*res;

	conv->minus = *conv->width < 0 ? 1 : conv->minus;
	*conv->width = ft_absolute(*conv->width);
	if ((int)(*conv->width - seq->len) >= 1)
	{
		if (!(res = (char *)ft_memalloc(sizeof(char) * (*conv->width))))
			return (NULL);
		str_mod_width_aux(res, seq, conv);
		free(seq->str);
		seq->str = res;
		seq->len = *conv->width;
	}
	return (seq);
}

t_seq			*str_conv(t_conv *conv, intmax_t n)
{
	t_seq	*seq;

	(void)n;
	if (!(seq = init_seq(NULL, 0)))
		return (NULL);
	if (!conv_arg(seq, conv) || !str_mod_width(seq, conv))
	{
		free(seq);
		return (NULL);
	}
	return (seq);
}
