/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_valid_unicode.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbero <rbarbero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/23 16:11:11 by rbarbero          #+#    #+#             */
/*   Updated: 2018/03/31 14:07:09 by rbarbero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <wchar.h>

int	ft_is_valid_unicode(wint_t wchar)
{
	if (wchar >= 0xd800 && wchar <= 0xdfff)
		return (0);
	return (1);
}
