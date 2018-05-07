/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_char_decode_utf8.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbero <rbarbero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/04 11:30:39 by rbarbero          #+#    #+#             */
/*   Updated: 2017/12/04 15:25:33 by rbarbero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

unsigned int	ft_char_decode_utf8(unsigned int c)
{
	if (c <= 0x7f)
		return (c);
	if (c <= 0xdfbf)
		c = (((c >> 8) & 0x1f) << 6) + (c & 0x3f);
	else if (c <= 0xefbfbf)
		c = (((c >> 16) & 0xf) << 12) + (((c >> 8) & 0x3f) << 6) + (c & 0x3f);
	else if (c <= 0xf7bfbfbf)
		c = (((c >> 24) & 0xf7) << 18) + (((c >> 16) & 0x3f) << 12)
			+ (((c >> 8) & 0x3f) << 6) + (c & 0x3f);
	return (c);
}
