/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_char_encode_utf8.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbero <rbarbero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/03 23:27:05 by rbarbero          #+#    #+#             */
/*   Updated: 2018/01/19 11:59:11 by rbarbero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

unsigned int	ft_char_encode_utf8(unsigned int c)
{
	if (c <= 0x7f)
		return (c);
	else if (c <= 0x7ff)
		c = ((0xc0 | c >> 6) << 8) + (0x80 | (c & 0x3f));
	else if (c <= 0xffff)
		c = ((0xe0 | c >> 12) << 16) + ((0x80 | ((c >> 6) & 0x3f)) << 8)
			+ (0x80 | (c & 0x3f));
	else if (c <= 0x10ffff)
		c = ((0xf0 | c >> 18) << 24) + ((0x80 | ((c >> 12) & 0x3f)) << 16)
			+ ((0x80 | ((c >> 6) & 0x3f)) << 8) + (0x80 | (c & 0x3f));
	return (c);
}
