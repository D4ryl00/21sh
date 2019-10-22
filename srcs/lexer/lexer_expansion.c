/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_expansion.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbero <rbarbero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/18 13:54:19 by rbarbero          #+#    #+#             */
/*   Updated: 2019/10/22 12:50:44 by rbarbero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "sh.h"
#include "lexer.h"

/*
** Case where a work is a variable: $i
*/

int	variable_expansion(t_buf *buffer, t_input *input
		, unsigned char f_params[2])
{
	(void)f_params;
	while (*(input->str) && *(input->str) != ' ' && *(input->str) != '\n')
	{
		if (ft_buf_add_char(buffer, *(input->str)) == -1)
			exit_perror(ENOMEM, NULL);
		(input->str)++;
	}
	return (0);
}

/*
** Case where a word begin by ${
*/

int	bracket_expansion(t_buf *buffer, t_input *input
		, unsigned char f_params[2])
{
	int	status;

	status = 0;
	while (42)
	{
		if (!*(input->str) && (newprompt(input, "> ") < 0))
			return (-1);
		else if (*(input->str) == '\'')
			status = sq_case(buffer, input, f_params);
		else if (*(input->str) == '"')
			status = dq_case(buffer, input, f_params);
		else if (*(input->str) == '\\')
			status = bs_case(buffer, input, f_params);
		else
		{
			if (ft_buf_add_char(buffer, *(input->str)) == -1)
				exit_perror(ENOMEM, NULL);
			(input->str)++;
			if (*(input->str - 1) == '}')
				break ;
		}
	}
	return (status);
}
