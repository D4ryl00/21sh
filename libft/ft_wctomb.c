/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wctomb.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbero <rbarbero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/17 13:30:36 by rbarbero          #+#    #+#             */
/*   Updated: 2018/01/23 17:38:39 by rbarbero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>
#include <wchar.h>

int	ft_wctomb(char *s, wchar_t wchar)
{
	int	ret;

	ret = 0;
	if (s && ((MB_CUR_MAX >= 1 && wchar <= 0x7f)
				|| (MB_CUR_MAX == 1 && wchar <= 0xff)) && (ret = 1))
		s[0] = wchar;
	else if (s && MB_CUR_MAX >= 2 && wchar <= 0x7ff && (ret = 2))
	{
		s[0] = 0xc0 | wchar >> 6;
		s[1] = 0x80 | (wchar & 0x3f);
	}
	else if (s && MB_CUR_MAX >= 3 && wchar <= 0xffff && (ret = 3))
	{
		s[0] = 0xe0 | wchar >> 12;
		s[1] = 0x80 | ((wchar >> 6) & 0x3f);
		s[2] = 0x80 | (wchar & 0x3f);
	}
	else if (s && MB_CUR_MAX >= 4 && wchar <= 0x10ffff && (ret = 4))
	{
		s[0] = 0xf0 | wchar >> 18;
		s[1] = 0x80 | ((wchar >> 12) & 0x3f);
		s[2] = 0x80 | ((wchar >> 6) & 0x3f);
		s[3] = 0x80 | (wchar & 0x3f);
	}
	return (ret);
}
