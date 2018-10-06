/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_token_expansion.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbero <rbarbero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/18 13:54:19 by rbarbero          #+#    #+#             */
/*   Updated: 2018/10/06 18:24:52 by rbarbero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "sh.h"

static int	variable_case(t_buf *buffer, t_input *input
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

int	dollar_case(t_buf *buffer, t_input *input
		, unsigned char f_params[2])
{
	if (ft_buf_add_char(buffer, *(input->str)) == -1)
		exit_perror(ENOMEM, NULL);
	(input->str)++;
	if (*(input->str) == '{')
		get_token_expansion(buffer, input, f_params);
	else if (*(input->str) == '(' && input->str[1] == '(')
		get_token_arithmetic(buffer, input, f_params);
	else if (*(input->str) == '(')
		substitution_case(buffer, input, f_params, ')');
	else
		variable_case(buffer, input, f_params);
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
				exit_perror(ENOMEM, NULL);
		}
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
			if (*(input->str - 1) == '}')
				break ;
		}
	}
	return (0);
}
