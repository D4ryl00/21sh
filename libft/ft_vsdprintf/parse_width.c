/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_width.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbero <rbarbero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/23 15:41:00 by rbarbero          #+#    #+#             */
/*   Updated: 2018/04/01 23:44:59 by rbarbero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_vsdprintf.h"
#include "libft.h"
#include <stdlib.h>

static UCHAR	parse_width_nbr(t_conv *conv, const char **fmt, t_list **args
		, int *arg_i)
{
	if (!(conv->width = (int *)malloc(sizeof(int))))
		return (0);
	*conv->width = ft_atoi(*fmt);
	while (*fmt && ft_isdigit(**fmt))
		(*fmt)++;
	if (**fmt == '*')
		return (parse_width(conv, fmt, args, arg_i));
	return (1);
}

static UCHAR	parse_width_dollar(t_conv *conv, const char **fmt, t_list **args
		, int *arg_i)
{
	int	nbr;

	nbr = ft_atoi(*fmt);
	while (*fmt && ft_isdigit(**fmt))
		(*fmt)++;
	if (*fmt && **fmt == '$' && (*fmt)++)
	{
		if (!new_arg(args, nbr, "d", (void **)&(conv->width)))
			return (0);
	}
	else
	{
		if (!(conv->width = (int *)malloc(sizeof(int))))
			return (0);
		*conv->width = nbr;
		if (!new_arg(args, conv->position, "d", NULL))
			return (0);
		conv->position = (*arg_i)++;
	}
	return (1);
}

UCHAR			parse_width(t_conv *conv, const char **fmt, t_list **args
		, int *arg_i)
{
	if (*fmt && ft_isdigit(**fmt))
		return (parse_width_nbr(conv, fmt, args, arg_i));
	else if (*fmt && **fmt == '*' && (*fmt)++)
	{
		if (*fmt && ft_isdigit(**fmt))
			return (parse_width_dollar(conv, fmt, args, arg_i));
		else
		{
			if (!new_arg(args, conv->position, "d", (void **)&(conv->width)))
				return (0);
			conv->position = (*arg_i)++;
		}
	}
	else
	{
		if (!(conv->width = (int *)malloc(sizeof(int))))
			return (0);
		*conv->width = 0;
	}
	return (1);
}
