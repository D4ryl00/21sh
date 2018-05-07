/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conv_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbero <rbarbero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/03 15:11:27 by rbarbero          #+#    #+#             */
/*   Updated: 2018/04/01 23:40:32 by rbarbero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_vsdprintf.h"
#include <stdlib.h>

void	init_convs(t_conv *convs, int nbr)
{
	int	i;

	i = -1;
	while (++i < nbr)
	{
		convs[i].position = 0;
		convs[i].hash = 0;
		convs[i].zero = 0;
		convs[i].minus = 0;
		convs[i].space = 0;
		convs[i].plus = 0;
		convs[i].quote = 0;
		convs[i].width = 0;
		convs[i].dot = 0;
		convs[i].precision = 0;
		ft_bzero(convs[i].modifier, 3);
		ft_bzero(convs[i].specifier, 2);
		convs[i].data = 0;
		convs[i].fconv = default_conv;
	}
}

t_seq	*init_seq(char *str, size_t len)
{
	t_seq	*seq;

	if (!(seq = (t_seq *)malloc(sizeof(t_seq))))
		return (NULL);
	seq->str = str;
	seq->len = len;
	return (seq);
}

t_seq	*print_conv(t_conv *conv, intmax_t n)
{
	if (conv->fconv)
		return (conv->fconv(conv, n));
	return (0);
}

void	free_convs(t_conv *convs, int nbr)
{
	(void)convs;
	(void)nbr;
}
