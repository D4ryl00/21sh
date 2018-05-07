/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   octal_conv.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbero <rbarbero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/22 10:01:05 by rbarbero          #+#    #+#             */
/*   Updated: 2018/04/01 23:44:20 by rbarbero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_vsdprintf.h"
#include "libft.h"
#include <stdlib.h>

static char	*conv_arg(t_conv *conv)
{
	if (conv->modifier[0] == 'h')
	{
		if (conv->modifier[1] == 'h')
			return (ft_uimtoa_base(*(unsigned char *)conv->data, 8));
		return (ft_uimtoa_base(*(unsigned short int *)conv->data, 8));
	}
	else if (conv->modifier[0] == 'l')
	{
		if (conv->modifier[1] == 'l')
			return (ft_uimtoa_base(*(unsigned long long int *)conv->data, 8));
		return (ft_uimtoa_base(*(unsigned long int *)conv->data, 8));
	}
	else if (conv->modifier[0] == 'j')
		return (ft_uimtoa_base(*(intmax_t *)conv->data, 8));
	else if (conv->modifier[0] == 'z')
		return (ft_uimtoa_base(*(size_t *)conv->data, 8));
	else
		return (ft_uimtoa_base(*(unsigned int *)conv->data, 8));
}

static char	*octal_mod_hash(char **str)
{
	char	*res;

	if (str && (*str)[0] != '0')
	{
		if (!(res = (char *)ft_memalloc(sizeof(char) * (ft_strlen(*str) + 2))))
			return (NULL);
		res[0] = '0';
		ft_strcat(res, *str);
		free(*str);
		*str = res;
	}
	return (*str);
}

t_seq		*octal_conv(t_conv *conv, intmax_t n)
{
	char	*res;
	t_seq	*seq;

	(void)n;
	if (conv->dot)
		conv->zero = 0;
	if (!(res = conv_arg(conv)))
		return (NULL);
	if (conv->dot && !int_mod_precision(&res, *conv->precision))
		return (NULL);
	if (conv->hash && !octal_mod_hash(&res))
		return (NULL);
	if (!int_mod_width(&res, conv))
		return (NULL);
	if (!(seq = init_seq(res, ft_strlen(res))))
		return (NULL);
	return (seq);
}
