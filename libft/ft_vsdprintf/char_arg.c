/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   char_arg.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbero <rbarbero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/15 22:16:24 by rbarbero          #+#    #+#             */
/*   Updated: 2018/04/01 23:40:09 by rbarbero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_vsdprintf.h"
#include "libft.h"
#include <stdarg.h>
#include <stdlib.h>
#include <wchar.h>

UCHAR	take_char_args(t_list *args, va_list va_args)
{
	char	modifier[3];

	get_modifier(modifier, ((t_arg *)args->content)->type);
	if (modifier[0] == 'l')
	{
		if (!(*(((t_arg *)args->content)->data) = malloc(sizeof(wint_t))))
			return (0);
		*((wint_t *)(*((t_arg *)args->content)->data)) = va_arg(va_args
				, wint_t);
	}
	else
	{
		if (!(*(((t_arg *)args->content)->data) = malloc(sizeof(int))))
			return (0);
		*((int *)(*((t_arg *)args->content)->data)) = va_arg(va_args, int);
	}
	return (1);
}
