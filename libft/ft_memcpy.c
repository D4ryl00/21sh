/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbero <rbarbero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/09 13:09:12 by rbarbero          #+#    #+#             */
/*   Updated: 2017/11/10 13:58:38 by rbarbero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t	i;
	char	*mem_dst;
	char	*mem_src;

	i = -1;
	mem_dst = (char *)dst;
	mem_src = (char *)src;
	while (++i < n)
		mem_dst[i] = mem_src[i];
	return (dst);
}
