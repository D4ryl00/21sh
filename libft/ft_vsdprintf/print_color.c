/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_color.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbero <rbarbero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/23 16:18:34 by rbarbero          #+#    #+#             */
/*   Updated: 2018/04/01 23:45:28 by rbarbero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_vsdprintf.h"
#include "libft.h"

static char	*get_color(const char *fmt, const char *p)
{
	if (!ft_strncmp(fmt, "{eoc}", p - fmt + 1))
		return (ft_strdup("\x1B[0m"));
	else if (!ft_strncmp(fmt, "{black}", p - fmt + 1))
		return (ft_strdup("\x1B[30m"));
	else if (!ft_strncmp(fmt, "{red}", p - fmt + 1))
		return (ft_strdup("\x1B[31m"));
	else if (!ft_strncmp(fmt, "{green}", p - fmt + 1))
		return (ft_strdup("\x1B[32m"));
	else if (!ft_strncmp(fmt, "{yellow}", p - fmt + 1))
		return (ft_strdup("\x1B[33m"));
	else if (!ft_strncmp(fmt, "{blue}", p - fmt + 1))
		return (ft_strdup("\x1B[35m"));
	else if (!ft_strncmp(fmt, "{magenta}", p - fmt + 1))
		return (ft_strdup("\x1B[36m"));
	else if (!ft_strncmp(fmt, "{cyan}", p - fmt + 1))
		return (ft_strdup("\x1B[37m"));
	else if (!ft_strncmp(fmt, "{white}", p - fmt + 1))
		return (ft_strdup("\x1B[38m"));
	else
		return (ft_strsub(fmt, 0, p - fmt + 1));
}

UCHAR		print_color(t_buffer *buf, const char **fmt)
{
	const char	*p;
	char		*color;

	p = *fmt;
	while (*p && *p != '}' && *p != '%')
		p++;
	if (*p == '}')
	{
		color = get_color(*fmt, p);
		if (!buf_add_str(buf, color))
			return (0);
		*fmt = p + 1;
	}
	else
	{
		if (!buf_add_str(buf, ft_strsub(*fmt, 0, p - *fmt)))
			return (0);
		*fmt = p;
	}
	return (1);
}
