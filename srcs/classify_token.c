/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   classify_token.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbero <rbarbero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/19 13:26:30 by rbarbero          #+#    #+#             */
/*   Updated: 2018/05/22 11:03:44 by rbarbero         ###   ########.fr       */
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

void	classify_ionumber_token(t_list *tokens)
{
	char	*str;

	while (tokens)
	{
		str = ((t_token *)tokens->content)->content;
		if (*str == '<' || *str == '>')
		{
			while (*str)
			{
				if (!ft_isdigit(*(str++)))
					break ;
			}
			if (!(*str))
				((t_token *)tokens->content)->type = IO_NUMBER;
		}
		else if (ft_isdigit(*str))
		{
			while (ft_isdigit(*str))
				str++;
			if ((*str == '>' || *str == '<') && !str[1])
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
