/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_quote.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbero <rbarbero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/18 13:48:53 by rbarbero          #+#    #+#             */
/*   Updated: 2019/10/11 17:50:20 by rbarbero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "sh.h"
#include "lexer.h"

static int	call_newprompt(t_input *input)
{
	free(input->save);
	input->save = NULL;
	if (newprompt(input, "> ") == -1)
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
	(input->str)++;
	if (!*(input->str) || *(input->str) == '\n')
	{
		if (call_newprompt(input) == -1)
			return (-1);
	}
	else if (*(input->str))
	{
		if (ft_buf_add_char(buffer, *(input->str)) == -1)
			exit_perror(ENOMEM, NULL);
		(input->str)++;
		f_params[0] = 1;
	}
	return (0);
}

static int	dq_case_req(t_buf *buffer, t_input *input
		, unsigned char f_params[2])
{
	int	status;

	status = 0;
	while (1)
	{
		if (!*(input->str) && (call_newprompt(input) == -1))
			return (-1);
		if (*(input->str) == '"')
			break ;
		else if (*(input->str) == '\\')
			status = bs_case(buffer, input, f_params);
		else if (*(input->str) == '$')
			status = dollar_case(buffer, input, f_params);
		else
		{
			if (ft_buf_add_char(buffer, *(input->str)) == -1)
				exit_perror(ENOMEM, NULL);
			(input->str)++;
		}
	}
	return (status);
}

int			dq_case(t_buf *buffer, t_input *input
		, unsigned char f_params[2])
{
	if (ft_buf_add_char(buffer, *(input->str)) == -1)
		exit_perror(ENOMEM, NULL);
	(input->str)++;
	if (dq_case_req(buffer, input, f_params) == -1)
		return (-1);
	if (ft_buf_add_char(buffer, *(input->str)) == -1)
		exit_perror(ENOMEM, NULL);
	(input->str)++;
	f_params[0] = 1;
	return (0);
}
