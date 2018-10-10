/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dprintf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbero <rbarbero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/01 19:00:56 by rbarbero          #+#    #+#             */
/*   Updated: 2018/10/10 11:24:57 by rbarbero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_vsdprintf.h"
#include <stdarg.h>

intmax_t	ft_dprintf(int fd, const char *format, ...)
{
	intmax_t	ret;
	va_list		va_args;

	va_start(va_args, format);
	ret = ft_vsdprintf(NULL, fd, format, va_args);
	va_end(va_args);
	return (ret);
}
