/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_arithmetic.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbero <rbarbero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/18 14:03:03 by rbarbero          #+#    #+#             */
/*   Updated: 2019/10/22 12:50:22 by rbarbero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "sh.h"
#include "lexer.h"

/*
** Case where a word begins by $((
*/

int	arithmetic_expansion(t_buf *buffer, t_input *input
		, unsigned char f_params[2])
{
	int	parenthesis;

	parenthesis = 2;
	while (42)
	{
		if (!*(input->str) && (newprompt(input, "> ") < 0))
			return (-1);
		else if (*(input->str) == '\'')
			sq_case(buffer, input, f_params);
		else if (*(input->str) == '"')
			dq_case(buffer, input, f_params);
		else if (*(input->str) == '\\')
			bs_case(buffer, input, f_params);
		else
		{
			if (ft_buf_add_char(buffer, *(input->str)) == -1)
				exit_perror(ENOMEM, NULL);
			(input->str)++;
			if (*(input->str - 1) == ')' && !(--parenthesis))
				break ;
		}
	}
	return (0);
}
