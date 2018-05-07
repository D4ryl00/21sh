/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_precision.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbero <rbarbero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/23 15:51:24 by rbarbero          #+#    #+#             */
/*   Updated: 2018/04/01 23:44:48 by rbarbero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_vsdprintf.h"
#include "libft.h"
#include <stdlib.h>

static UCHAR	parse_precision_star(t_conv *conv, const char **fmt
		, t_list **args, int *arg_i)
{
	int			nbr;

	if (*fmt && ft_isdigit(**fmt))
	{
		nbr = ft_atoi(*fmt);
		while (*fmt && ft_isdigit(**fmt))
			(*fmt)++;
		if (*fmt && **fmt == '$' && (*fmt)++)
			if (!new_arg(args, nbr, "d", (void **)&(conv->precision)))
				return (0);
	}
	else
	{
		if (!new_arg(args, conv->position, "d", (void **)&(conv->precision)))
			return (0);
		conv->position = (*arg_i)++;
	}
	return (1);
}

static UCHAR	parse_precision_dot(t_conv *conv, const char **fmt
		, t_list **args, int *arg_i)
{
	int	nbr;

	conv->dot = 1;
	if (++(*fmt) && ft_isdigit(**fmt))
	{
		nbr = ft_atoi(*fmt);
		if (!(conv->precision = (int *)malloc(sizeof(int))))
			return (0);
		*conv->precision = nbr;
		while (*fmt && ft_isdigit(**fmt))
			(*fmt)++;
	}
	else if (*fmt && **fmt == '*' && (*fmt)++)
		return (parse_precision_star(conv, fmt, args, arg_i));
	else
	{
		if (!(conv->precision = (int *)malloc(sizeof(int))))
			return (0);
		*conv->precision = 0;
	}
	return (1);
}

UCHAR			parse_precision(t_conv *conv, const char **fmt, t_list **args
		, int *arg_i)
{
	if (*fmt && **fmt == '.')
		return (parse_precision_dot(conv, fmt, args, arg_i));
	else
	{
		if (!(conv->precision = (int *)malloc(sizeof(int))))
			return (0);
		*conv->precision = 0;
	}
	return (1);
}
