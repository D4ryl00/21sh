/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   n_arg.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbero <rbarbero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/22 16:45:14 by rbarbero          #+#    #+#             */
/*   Updated: 2018/04/01 23:44:04 by rbarbero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_vsdprintf.h"
#include "libft.h"
#include <stdarg.h>
#include <stdlib.h>

UCHAR	take_n_args(t_list *args, va_list va_args)
{
	char	modifier[3];

	get_modifier(modifier, ((t_arg *)args->content)->type);
	if (modifier[0] == 'l' && modifier[1] == 'l')
		*((t_arg *)args->content)->data = va_arg(va_args, long long int *);
	else if (modifier[0] == 'l')
		*((t_arg *)args->content)->data = va_arg(va_args, long int *);
	else if (modifier[0] == 'j')
		*((t_arg *)args->content)->data = va_arg(va_args, intmax_t *);
	else if (modifier[0] == 'z')
		*((t_arg *)args->content)->data = va_arg(va_args, size_t *);
	else
		*((t_arg *)args->content)->data = va_arg(va_args, int *);
	return (1);
}
