/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_substitution.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbero <rbarbero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/18 14:05:57 by rbarbero          #+#    #+#             */
/*   Updated: 2019/10/11 17:39:41 by rbarbero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "sh.h"
#include "lexer.h"

static int	loop_case(t_buf *buffer, t_input *input
		, unsigned char f_params[2], char close)
{
	int	status;

	status = 0;
	while (42)
	{
		if (!*(input->str) && (newprompt(input, "> ") == -1))
			return (-1);
		else if (*(input->str) == '\'')
			status = sq_case(buffer, input, f_params);
		else if (*(input->str) == '"')
			status = dq_case(buffer, input, f_params);
		else if (*(input->str) == '\\')
			status = bs_case(buffer, input, f_params);
		else if (*(input->str) == '$')
			status = dollar_case(buffer, input, f_params);
		else
		{
			if (ft_buf_add_char(buffer, *(input->str)) == -1)
				exit_perror(ENOMEM, NULL);
			if ((input->str)++ && *(input->str - 1) == close)
				break ;
		}
	}
	return (status);
}

/*
** Case where a word begins by $( or `
*/

int			substitution_case(t_buf *buffer, t_input *input
		, unsigned char f_params[2], char close)
{
	int	status;

	status = 0;
	if (ft_buf_add_char(buffer, *(input->str)) == -1)
		exit_perror(ENOMEM, NULL);
	(input->str)++;
	status = loop_case(buffer, input, f_params, close);
	f_params[0] = 1;
	return (status);
}
