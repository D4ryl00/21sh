/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbero <rbarbero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/14 16:10:58 by rbarbero          #+#    #+#             */
/*   Updated: 2017/11/14 22:07:11 by rbarbero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static int	get_size(int n)
{
	int	size;

	size = 1;
	while (n /= 10)
		size++;
	return (size);
}

static void	complete_str(char *s, int n, int size, int minus)
{
	int	i;
	int	coef;

	coef = minus ? -1 : 1;
	i = size + minus;
	while (--i >= 0)
	{
		s[i] = coef * (n % 10) + '0';
		n /= 10;
	}
	if (minus)
		s[0] = '-';
}

char		*ft_itoa(int n)
{
	int		size;
	char	*str;
	int		minus;

	minus = n < 0 ? 1 : 0;
	size = get_size(n);
	if (!(str = (char *)malloc(size + minus + 1)))
		return (NULL);
	str[size + minus] = '\0';
	complete_str(str, n, size, minus);
	return (str);
}
