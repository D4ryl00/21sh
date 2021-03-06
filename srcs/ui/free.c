/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbero <rbarbero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/18 14:21:56 by rbarbero          #+#    #+#             */
/*   Updated: 2018/10/07 12:20:18 by rbarbero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "sh.h"
#include "parser.h"

void	token_free(void *content, size_t size)
{
	(void)size;
	if (content)
	{
		if (((t_token *)content)->content)
			free(((t_token *)content)->content);
		free(content);
	}
}
