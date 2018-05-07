/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbero <rbarbero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 14:46:28 by rbarbero          #+#    #+#             */
/*   Updated: 2017/11/15 14:47:59 by rbarbero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	int	size;
	int	tmp;

	if (n < 0)
		ft_putchar_fd('-', fd);
	else
		n = -n;
	tmp = n;
	size = 1;
	while (tmp /= 10)
		size *= 10;
	while (size)
	{
		ft_putchar_fd(-((n / size) % 10) + '0', fd);
		size /= 10;
	}
}
