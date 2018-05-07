/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbero <rbarbero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/21 15:50:02 by rbarbero          #+#    #+#             */
/*   Updated: 2018/04/01 23:44:30 by rbarbero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_vsdprintf.h"
#include "libft.h"
#include <stdarg.h>
#include <stdlib.h>

static UCHAR	parse_conv(t_conv *conv, const char **format, t_list **args
		, int *arg_i)
{
	char	type[4];

	type[0] = '\0';
	parse_position_arg(conv, format, arg_i);
	parse_flags(conv, format);
	if (!parse_width(conv, format, args, arg_i))
		return (0);
	if (!parse_precision(conv, format, args, arg_i))
		return (0);
	parse_modifier(conv, format);
	if (!parse_specifier(conv, format))
		return (0);
	ft_strcat(type, conv->modifier);
	ft_strcat(type, conv->specifier);
	if (conv->specifier[0] && conv->specifier[0] != '%')
		new_arg(args, conv->position, type, &(conv->data));
	else
		(*arg_i)--;
	return (1);
}

UCHAR			parse_format(t_conv *convs, const char *format, va_list va_args)
{
	t_list	*args;
	int		arg_i;
	int		conv_i;

	args = NULL;
	conv_i = 0;
	arg_i = 0;
	while (*format)
	{
		while (*format && *format != '%')
			format++;
		if (*format && format++
				&& !parse_conv(&(convs[conv_i++]), &format, &args, &arg_i))
			return (0);
	}
	if (args)
		take_args(&args, va_args);
	return (1);
}
