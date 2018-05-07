/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_arg.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbero <rbarbero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/18 09:40:24 by rbarbero          #+#    #+#             */
/*   Updated: 2018/04/01 23:45:39 by rbarbero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_vsdprintf.h"
#include "libft.h"
#include <stdarg.h>
#include <stdlib.h>
#include <wchar.h>

UCHAR	take_str_args(t_list *args, va_list va_args)
{
	char	modifier[3];

	get_modifier(modifier, ((t_arg *)args->content)->type);
	if (modifier[0] == 'l')
	{
		if (!(*(((t_arg *)args->content)->data) = malloc(sizeof(wchar_t *))))
			return (0);
		*((wchar_t **)(*((t_arg *)args->content)->data)) = va_arg(va_args
				, wchar_t *);
	}
	else
	{
		if (!(*(((t_arg *)args->content)->data) = malloc(sizeof(char *))))
			return (0);
		*((char **)(*((t_arg *)args->content)->data)) = va_arg(va_args, char *);
	}
	return (1);
}
