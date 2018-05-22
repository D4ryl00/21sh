/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   classify_token.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbero <rbarbero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/19 13:26:30 by rbarbero          #+#    #+#             */
/*   Updated: 2018/05/22 10:32:48 by rbarbero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "sh.h"

void	classify_token_operator(t_list *tokens)
{
	int	i;

	while (tokens)
	{
		i = -1;
		while (g_op_token[++i])
		{
			if (!ft_strcmp(g_op_token[i]
						, ((t_token *)tokens->content)->content))
			{
				((t_token *)tokens->content)->type = i;
				break ;
			}
		}
		tokens = tokens->next;
	}
}

int	classify_token(t_list *tokens)
{
	classify_token_operator(tokens);
	return (0);
}
