/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   int_conv.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbero <rbarbero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/22 10:01:05 by rbarbero          #+#    #+#             */
/*   Updated: 2018/04/01 23:43:26 by rbarbero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_vsdprintf.h"
#include "libft.h"

static char	*conv_arg(t_conv *conv)
{
	if (conv->modifier[0] == 'h')
	{
		if (conv->modifier[1] == 'h')
			return (ft_imtoa_base(*(signed char *)conv->data, 10));
		return (ft_imtoa_base(*(short int *)conv->data, 10));
	}
	else if (conv->modifier[0] == 'l')
	{
		if (conv->modifier[1] == 'l')
			return (ft_imtoa_base(*(long long int *)conv->data, 10));
		return (ft_imtoa_base(*(long int *)conv->data, 10));
	}
	else if (conv->modifier[0] == 'j')
		return (ft_imtoa_base(*(intmax_t *)conv->data, 10));
	else if (conv->modifier[0] == 'z')
		return (ft_imtoa_base(*(size_t *)conv->data, 10));
	else
		return (ft_imtoa_base(*(int *)conv->data, 10));
}

t_seq		*int_conv(t_conv *conv, intmax_t n)
{
	char	*res;
	t_seq	*seq;

	(void)n;
	if (conv->zero && *conv->precision > 0)
		conv->zero = 0;
	if (!(res = conv_arg(conv)))
		return (NULL);
	if (conv->dot && !int_mod_precision(&res, *conv->precision))
		return (NULL);
	if (conv->quote && !int_mod_quote(&res))
		return (NULL);
	if (conv->plus && res[0] != '-' && !int_mod_plus(&res))
		return (NULL);
	if (conv->space && !int_mod_space(&res))
		return (NULL);
	if (!int_mod_width(&res, conv))
		return (NULL);
	if (!(seq = init_seq(res, ft_strlen(res))))
		return (NULL);
	return (seq);
}
