/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   classify_token.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbero <rbarbero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/19 13:26:30 by rbarbero          #+#    #+#             */
/*   Updated: 2018/10/02 22:52:01 by rbarbero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "sh.h"

enum e_token	token_get_op_type(char *str)
{
	int	i;

	i = 10;
	if (str)
	{
		if ((i = ft_strarrchr(str, g_op_token)) != -1)
			return (i);
		if ((i = ft_strarrchr(str, g_control_operator)) != -1)
			return ((enum e_token)CONTROL);
		i = 10;
	}
	return (i);
}
