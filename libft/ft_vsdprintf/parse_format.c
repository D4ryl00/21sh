/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_format.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbero <rbarbero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/21 15:50:17 by rbarbero          #+#    #+#             */
/*   Updated: 2018/04/01 23:44:39 by rbarbero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_vsdprintf.h"
#include "libft.h"
#include <stdlib.h>

void		parse_position_arg(t_conv *conv, const char **fmt, int *arg_i)
{
	const char	*format;
	int			i;

	format = *fmt;
	if (ft_isdigit(*format))
	{
		i = 1;
		while (ft_isdigit(*(format + i)))
			i++;
		if (*(format + i) == '$')
		{
			conv->position = ft_atoi(format);
			*fmt = format + i + 1;
		}
		else
			conv->position = (*arg_i)++;
	}
	else
		conv->position = (*arg_i)++;
}

void		parse_flags(t_conv *conv, const char **fmt)
{
	const char	*format;

	format = *fmt;
	while (*format && ft_strchr(FLAGS_CHAR, *format))
	{
		if (*format == '#')
			conv->hash = 1;
		else if (*format == '0' && !conv->minus)
			conv->zero = 1;
		else if (*format == '-' && !(conv->minus = 0))
			conv->minus = 1;
		else if (*format == ' ' && !conv->plus)
			conv->space = 1;
		else if (*format == '+' && !(conv->space = 0))
			conv->plus = 1;
		else if (*format == '\'')
			conv->quote = 1;
		format++;
	}
	*fmt = format;
}

void		parse_modifier(t_conv *conv, const char **fmt)
{
	UCHAR	i;

	i = 0;
	if (**fmt && ft_strchr("hljz", **fmt))
	{
		conv->modifier[i++] = **fmt;
		(*fmt)++;
		if (*fmt && (**fmt == 'h' || **fmt == 'l'))
		{
			conv->modifier[i++] = **fmt;
			(*fmt)++;
		}
	}
}

static void	parse_specifier_aux(t_conv *conv)
{
	if (conv->specifier[0] == 'd' || conv->specifier[0] == 'i')
		conv->fconv = int_conv;
	else if (conv->specifier[0] == 'u')
		conv->fconv = uint_conv;
	else if (ft_strchr("xXp", conv->specifier[0]))
		conv->fconv = hex_conv;
	else if (conv->specifier[0] == 'o')
		conv->fconv = octal_conv;
	else if (conv->specifier[0] == 'b')
		conv->fconv = bin_conv;
	else if (conv->specifier[0] == 'c')
		conv->fconv = char_conv;
	else if (conv->specifier[0] == 's')
		conv->fconv = str_conv;
	else if (conv->specifier[0] == 'n')
		conv->fconv = n_conv;
	else if (conv->specifier[0] == '%')
		conv->fconv = percent_conv;
}

UCHAR		parse_specifier(t_conv *conv, const char **fmt)
{
	if (**fmt && ft_strchr(CONV_SPEC, **fmt))
	{
		conv->specifier[0] = **fmt;
		(*fmt)++;
		if (ft_strchr("DOUCSp", conv->specifier[0]))
		{
			ft_strcpy(conv->modifier, "l");
			ft_strtolower(conv->specifier);
		}
		parse_specifier_aux(conv);
		conv->hash = conv->specifier[0] == 'p' ? 1 : conv->hash;
	}
	else if (*fmt)
	{
		if (!(conv->data = (char *)malloc(sizeof(char))))
			return (0);
		*(char *)conv->data = **fmt;
		if (**fmt)
			(*fmt)++;
	}
	return (1);
}
