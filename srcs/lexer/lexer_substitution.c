/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_substitution.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbero <rbarbero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/18 14:05:57 by rbarbero          #+#    #+#             */
/*   Updated: 2018/10/07 11:55:37 by rbarbero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "sh.h"
#include "lexer.h"

/*
** Case where a word begins by $( or `
*/

int	substitution_case(t_buf *buffer, t_input *input
		, unsigned char f_params[2], char close)
{
	if (ft_buf_add_char(buffer, *(input->str)) == -1)
		exit_perror(ENOMEM, NULL);
	(input->str)++;
	while (42)
	{
		if (!*(input->str) && (newprompt(input, "> ") == -1))
			return (-1);
		else if (*(input->str) == '\'')
			sq_case(buffer, input, f_params);
		else if (*(input->str) == '"')
			dq_case(buffer, input, f_params);
		else if (*(input->str) == '\\')
			bs_case(buffer, input, f_params);
		else if (*(input->str) == '$')
			dollar_case(buffer, input, f_params);
		else
		{
			if (ft_buf_add_char(buffer, *(input->str)) == -1)
				exit_perror(ENOMEM, NULL);
			if ((input->str)++ && *(input->str - 1) == close)
				break ;
		}
	}
	f_params[0] = 1;
	return (0);
}
