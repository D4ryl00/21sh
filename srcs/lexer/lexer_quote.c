/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_quote.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbero <rbarbero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/18 13:48:53 by rbarbero          #+#    #+#             */
/*   Updated: 2018/10/06 00:12:22 by rbarbero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "sh.h"

int			sq_case(t_buf *buffer, t_input *input
		, unsigned char f_params[2])
{
	if (ft_buf_add_char(buffer, *(input->str)) == -1)
		exit_perror(ENOMEM, NULL);
	(input->str)++;
	while (1)
	{
		if (!*(input->str))
		{
			free(input->save);
			if (!newprompt(input, "> "))
				exit_perror(ENOMEM, NULL);
		}
		else if (*(input->str) == '\'')
			break ;
		else
		{
			if (ft_buf_add_char(buffer, *(input->str)) == -1)
				exit_perror(ENOMEM, NULL);
			(input->str)++;
		}
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
		free(input->save);
		if (!newprompt(input, "> "))
			exit_perror(ENOMEM, NULL);
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

static void	dq_case_req(t_buf *buffer, t_input *input
		, unsigned char f_params[2])
{
	while (1)
	{
		if (!*(input->str))
		{
			free(input->save);
			if (!newprompt(input, "> "))
				exit_perror(ENOMEM, NULL);
		}
		if (*(input->str) == '"')
			break ;
		else if (*(input->str) == '\\')
			bs_case(buffer, input, f_params);
		else if (*(input->str) == '$')
			dollar_case(buffer, input, f_params);
		else
		{
			if (ft_buf_add_char(buffer, *(input->str)) == -1)
				exit_perror(ENOMEM, NULL);
			(input->str)++;
		}
	}
}

int			dq_case(t_buf *buffer, t_input *input
		, unsigned char f_params[2])
{
	if (ft_buf_add_char(buffer, *(input->str)) == -1)
		exit_perror(ENOMEM, NULL);
	(input->str)++;
	dq_case_req(buffer, input, f_params);
	if (ft_buf_add_char(buffer, *(input->str)) == -1)
		exit_perror(ENOMEM, NULL);
	(input->str)++;
	f_params[0] = 1;
	return (0);
}

