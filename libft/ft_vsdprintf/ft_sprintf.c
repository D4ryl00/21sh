/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sprintf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbero <rbarbero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/01 16:36:17 by rbarbero          #+#    #+#             */
/*   Updated: 2018/10/10 11:25:35 by rbarbero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_vsdprintf.h"
#include <stdarg.h>

intmax_t	ft_sprintf(char **str, const char *format, ...)
{
	intmax_t	ret;
	va_list		va_args;

	va_start(va_args, format);
	ret = ft_vsdprintf(str, -1, format, va_args);
	va_end(va_args);
	return (ret);
}
