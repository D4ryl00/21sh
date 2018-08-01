/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   classify_token.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbero <rbarbero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/19 13:26:30 by rbarbero          #+#    #+#             */
/*   Updated: 2018/08/01 17:01:18 by rbarbero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "sh.h"

void	classify_operator_token(t_list *tokens)
{
	int	i;

	while (tokens)
	{
		i = -1;
		while (*g_op_token[++i])
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

void	classify_ionumber_token(t_list *tokens)
{
	char	*str;
	t_list	*next_token;
	char	*next_str;

	while (tokens)
	{
		str = ((t_token *)tokens->content)->content;
		if (ft_isstrdigit(str) && (next_token = tokens->next))
		{
			next_str = ((t_token *)next_token->content)->content;
			if (*next_str == '<' || *next_str == '>')
				((t_token *)tokens->content)->type = IO_NUMBER;
		}
		tokens = tokens->next;
	}
}

int	classify_token(t_list *tokens)
{
	classify_operator_token(tokens);
	classify_ionumber_token(tokens);
	return (0);
}
