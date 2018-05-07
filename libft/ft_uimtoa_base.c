/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_uimtoa_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbero <rbarbero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/18 17:41:30 by rbarbero          #+#    #+#             */
/*   Updated: 2018/01/18 17:41:44 by rbarbero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static int	get_size(uintmax_t n, int base)
{
	int	size;

	size = 1;
	while (n / base)
	{
		size++;
		n /= base;
	}
	return (size);
}

static char	conv_digit(uintmax_t n, int base)
{
	int	digit;

	digit = n % base;
	if (digit < 10)
		digit += '0';
	else
		digit += 'a' - 10;
	return (digit);
}

char		*ft_uimtoa_base(uintmax_t n, int base)
{
	char	*res;
	int		len;
	int		i;

	len = get_size(n, base);
	if (!(res = (char *)ft_memalloc(sizeof(char) * (len + 1))))
		return (NULL);
	i = len;
	while (--i >= 0)
	{
		res[i] = conv_digit(n, base);
		n /= base;
	}
	return (res);
}
