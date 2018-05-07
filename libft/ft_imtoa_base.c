/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_imtoa_base.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbero <rbarbero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/18 17:41:10 by rbarbero          #+#    #+#             */
/*   Updated: 2018/01/18 17:41:16 by rbarbero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static int	get_size(intmax_t n, int base)
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

static char	conv_digit(intmax_t n, int base, int neg)
{
	int	digit;

	digit = (neg ? -1 : 1) * (n % base);
	if (digit < 10)
		digit += '0';
	else
		digit += 'a' - 10;
	return (digit);
}

char		*ft_imtoa_base(intmax_t n, int base)
{
	char	*res;
	int		len;
	int		neg;
	int		i;

	neg = n < 0 ? 1 : 0;
	len = get_size(n, base);
	if (!(res = (char *)ft_memalloc(sizeof(char) * (len + neg + 1))))
		return (NULL);
	if (neg)
		res[0] = '-';
	i = len + neg;
	while (--i >= 0 + neg)
	{
		res[i] = conv_digit(n, base, neg);
		n /= base;
	}
	return (res);
}
