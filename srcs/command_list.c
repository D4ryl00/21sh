/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_list.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbero <rbarbero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/11 22:27:45 by rbarbero          #+#    #+#             */
/*   Updated: 2018/09/12 01:17:59 by rbarbero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "sh.h"
#include <stdlib.h>

t_list	*make_command_list(t_list *tokens)
{
	t_list	*lcmd;

	lcmd = NULL;
	while (tokens)
	{
		if (!lcmd || ((!ft_strcmp(tokens->content, ";")
				|| !ft_strcmp(tokens->content, "&")) && tokens->next))
			if (!(lcmd = (t_list *)malloc(sizeof(t_list))))
				exit_perror(ENOMEM, NULL);
		tokens = tokens->next;
	}
	return (0);
}
