/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbero <rbarbero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/10 14:49:29 by rbarbero          #+#    #+#             */
/*   Updated: 2017/11/17 11:04:06 by rbarbero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	unsigned long	nbr;
	int				coef;

	nbr = 0;
	coef = 1;
	while (ft_isspace(*str))
		str++;
	if (*str == '+' || *str == '-')
		coef = *str++ == '-' ? -1 : 1;
	while (*str >= '0' && *str <= '9')
	{
		nbr = nbr * 10 + (*str++ - '0');
		if (coef == 1 && nbr > 0x7FFFFFFFFFFFFFFF)
			return (-1);
		if (coef == -1 && nbr > 0x8000000000000000)
			return (0);
	}
	return (coef == 1 ? (int)nbr : (int)-nbr);
}
