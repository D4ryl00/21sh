/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_token_substitution.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbero <rbarbero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/18 14:05:57 by rbarbero          #+#    #+#             */
/*   Updated: 2018/05/18 14:06:55 by rbarbero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "sh.h"

int	substitution_case(t_buf *buffer, t_input *input
		, unsigned char f_params[2], char close)
{
	while (42)
	{
		if (!*(input->str))
		{
			free(input->save);
			if (!newprompt(input, "> "))
				exit_perror(EOTHER, "syntax error");
		}
		if (*(input->str) == close)
			break ;
		else if (*(input->str) == '\'')
			sq_case(buffer, input, f_params);
		else if (*(input->str) == '"')
			dq_case(buffer, input, f_params);
		else if (*(input->str) == '\\')
			bs_case(buffer, input, f_params);
		else if (*(input->str) == '$')
			dollar_case(buffer, input, f_params);
		else if (*(input->str) == '`')
			bq_input(buffer, input, f_params);
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

int	bq_input(t_buf *buffer, t_input *input
		, unsigned char f_params[2])
{
	ft_buf_add_char(buffer, *(input->str));
	(input->str)++;
	if (*(input->str))
	{
		ft_buf_add_char(buffer, *(input->str));
		(input->str)++;
	}
	f_params[0] = 1;
	return (0);
}
