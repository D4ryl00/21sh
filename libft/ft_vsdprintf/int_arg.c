/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   int_arg.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbero <rbarbero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/21 15:33:09 by rbarbero          #+#    #+#             */
/*   Updated: 2018/04/01 23:43:17 by rbarbero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_vsdprintf.h"
#include "libft.h"
#include <stdarg.h>
#include <stdlib.h>

static UCHAR	llmodifier(t_list *args, va_list va_args)
{
	if (!(*(((t_arg *)args->content)->data) = malloc(sizeof(long long int))))
		return (0);
	*((long long int *)(*((t_arg *)args->content)->data)) = va_arg(va_args
			, long long int);
	return (1);
}

static UCHAR	lmodifier(t_list *args, va_list va_args)
{
	if (!(*(((t_arg *)args->content)->data) = malloc(sizeof(long int))))
		return (0);
	*((long int *)(*((t_arg *)args->content)->data)) = va_arg(va_args
			, long int);
	return (1);
}

static UCHAR	jmodifier(t_list *args, va_list va_args)
{
	if (!(*(((t_arg *)args->content)->data) = malloc(sizeof(intmax_t))))
		return (0);
	*((intmax_t *)(*((t_arg *)args->content)->data)) =
		va_arg(va_args, intmax_t);
	return (1);
}

static UCHAR	zmodifier(t_list *args, va_list va_args)
{
	if (!(*(((t_arg *)args->content)->data) = malloc(sizeof(size_t))))
		return (0);
	*((size_t *)(*((t_arg *)args->content)->data)) = va_arg(va_args, size_t);
	return (1);
}

UCHAR			take_int_args(t_list *args, va_list va_args)
{
	char	modifier[3];

	get_modifier(modifier, ((t_arg *)args->content)->type);
	if (modifier[0] == 'l' && modifier[1] == 'l')
		return (llmodifier(args, va_args));
	else if (modifier[0] == 'l')
		return (lmodifier(args, va_args));
	else if (modifier[0] == 'j')
		return (jmodifier(args, va_args));
	else if (modifier[0] == 'z')
		return (zmodifier(args, va_args));
	else if (!((t_arg *)args->content)->data)
		va_arg(va_args, int);
	else
	{
		if (!(*(((t_arg *)args->content)->data) = malloc(sizeof(int))))
			return (0);
		*((int *)(*((t_arg *)args->content)->data)) = va_arg(va_args, int);
	}
	return (1);
}
