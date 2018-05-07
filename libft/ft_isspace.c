/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isspace.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbero <rbarbero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/13 13:57:16 by rbarbero          #+#    #+#             */
/*   Updated: 2017/11/16 21:29:35 by rbarbero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isspace(int c)
{
	if ((unsigned char)c == '\t' || (unsigned char)c == '\n'
			|| (unsigned char)c == '\v' || (unsigned char)c == '\f'
			|| (unsigned char)c == '\r' || (unsigned char)c == ' ')
		return (1);
	return (0);
}
