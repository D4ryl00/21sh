/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_token_expansion.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbero <rbarbero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/18 13:54:19 by rbarbero          #+#    #+#             */
/*   Updated: 2018/05/18 14:05:45 by rbarbero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "sh.h"

int	dollar_case(t_buf *buffer, t_input *input
		, unsigned char f_params[2])
{
	ft_buf_add_char(buffer, *(input->str));
	(input->str)++;
	if (*(input->str) == '{')
		get_token_expansion(buffer, input, f_params);
	else if (*(input->str) == '(' && input->str[1] == '(')
		get_token_arithmetic(buffer, input, f_params);
	else if (*(input->str) == '(')
		substitution_case(buffer, input, f_params, ')');
	f_params[0] = 1;
	return (0);
}

int	get_token_expansion(t_buf *buffer, t_input *input
		, unsigned char f_params[2])
{
	while (42)
	{
		if (!*(input->str))
		{
			free(input->save);
			if (!newprompt(input, "> "))
				exit_perror(EOTHER, "syntax error");
		}
		if (*(input->str) == '}')
			break ;
		else if (*(input->str) == '\'')
			sq_case(buffer, input, f_params);
		else if (*(input->str) == '"')
			dq_case(buffer, input, f_params);
		else if (*(input->str) == '\\')
			bs_case(buffer, input, f_params);
		else
		{
			ft_buf_add_char(buffer, *(input->str));
			(input->str)++;
		}
	}
	ft_buf_add_char(buffer, *(input->str));
	(input->str)++;
	return (0);
}
