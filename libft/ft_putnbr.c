/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbero <rbarbero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 13:00:22 by rbarbero          #+#    #+#             */
/*   Updated: 2017/11/15 13:39:34 by rbarbero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr(int n)
{
	int	size;
	int	tmp;

	if (n < 0)
		ft_putchar('-');
	else
		n = -n;
	tmp = n;
	size = 1;
	while (tmp /= 10)
		size *= 10;
	while (size)
	{
		ft_putchar(-((n / size) % 10) + '0');
		size /= 10;
	}
}
