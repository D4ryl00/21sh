/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   n_conv.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbero <rbarbero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/22 16:03:48 by rbarbero          #+#    #+#             */
/*   Updated: 2018/04/01 23:44:12 by rbarbero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_vsdprintf.h"
#include "libft.h"

t_seq			*n_conv(t_conv *conv, intmax_t n)
{
	t_seq	*seq;

	if (conv->modifier[0] == 'h' && conv->modifier[1] == 'h')
		*(signed char *)(conv->data) = (signed char)n;
	else if (conv->modifier[0] == 'l')
		*(short int *)(conv->data) = (short int)n;
	if (conv->modifier[0] == 'l' && conv->modifier[1] == 'l')
		*(long long int *)(conv->data) = (long long int)n;
	else if (conv->modifier[0] == 'l')
		*(long int *)(conv->data) = (long int)n;
	else if (conv->modifier[0] == 'j')
		*(intmax_t *)(conv->data) = (intmax_t)n;
	else if (conv->modifier[0] == 'z')
		*(size_t *)(conv->data) = (size_t)n;
	else
		*(int *)(conv->data) = n;
	if (!(seq = init_seq(ft_strdup(""), 0)))
		return (NULL);
	return (seq);
}
