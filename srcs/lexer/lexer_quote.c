/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_quote.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbero <rbarbero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/18 13:48:53 by rbarbero          #+#    #+#             */
/*   Updated: 2019/10/23 17:37:47 by rbarbero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "sh.h"
#include "lexer.h"

static int	call_newprompt(t_input *input)
{
	free(input->save);
	input->save = NULL;
	if (newprompt(input, "> ") < 0)
		return (-1);
	return (0);
}

int			sq_case(t_buf *buffer, t_input *input
		, unsigned char f_params[2])
{
	if (ft_buf_add_char(buffer, *(input->str)) == -1)
		exit_perror(ENOMEM, NULL);
	(input->str)++;
	while (1)
		if (!*(input->str))
		{
			if (call_newprompt(input) == -1)
				return (-1);
		}
		else if (*(input->str) == '\'')
			break ;
		else
		{
			if (ft_buf_add_char(buffer, *(input->str)) == -1)
				exit_perror(ENOMEM, NULL);
			(input->str)++;
		}
	if (ft_buf_add_char(buffer, *(input->str)) == -1)
		exit_perror(ENOMEM, NULL);
	(input->str)++;
	f_params[0] = 1;
	return (0);
}

int			bs_case(t_buf *buffer, t_input *input
		, unsigned char f_params[2])
{
	if (!input->str[1] || (input->str[1] == '\n'))
	{
		if (call_newprompt(input) == -1)
			return (-1);
	}
	else if (*(input->str))
	{
		if (ft_buf_add_nstr(buffer, input->str, 2) == -1)
			exit_perror(ENOMEM, NULL);
		input->str += 2;
		f_params[0] = 1;
	}
	return (0);
}

static int	dq_case_req(t_buf *buffer, t_input *input)
{
	while (1)
	{
		if (!*(input->str) && (call_newprompt(input) == -1))
			return (-1);
		if (*(input->str) == '"')
			break ;
		else if (*(input->str) == '\\')
		{
			if (!input->str[1] || (input->str[1] == '\n'))
			{
				if (call_newprompt(input) == -1)
					return (-1);
				continue ;
			}
			if (ft_buf_add_nstr(buffer, input->str, 2) == -1)
				exit_perror(ENOMEM, NULL);
			input->str += 2;
		}
		else if (ft_buf_add_char(buffer, *(input->str++)) == -1)
			exit_perror(ENOMEM, NULL);
	}
	return (0);
}

int			dq_case(t_buf *buffer, t_input *input
		, unsigned char f_params[2])
{
	if (ft_buf_add_char(buffer, *(input->str)) == -1)
		exit_perror(ENOMEM, NULL);
	(input->str)++;
	if (dq_case_req(buffer, input) == -1)
		return (-1);
	if (ft_buf_add_char(buffer, *(input->str)) == -1)
		exit_perror(ENOMEM, NULL);
	(input->str)++;
	f_params[0] = 1;
	return (0);
}
