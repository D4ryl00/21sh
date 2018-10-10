/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_misc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbero <rbarbero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/18 14:24:53 by rbarbero          #+#    #+#             */
/*   Updated: 2018/10/07 12:09:47 by rbarbero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "sh.h"
#include "lexer.h"

/*
** Case where a word begins with $ char.
*/

int	dollar_case(t_buf *buffer, t_input *input
		, unsigned char f_params[2])
{
	if (ft_buf_add_char(buffer, *(input->str)) == -1)
		exit_perror(ENOMEM, NULL);
	(input->str)++;
	if (*(input->str) == '{')
		bracket_expansion(buffer, input, f_params);
	else if (*(input->str) == '(' && input->str[1] == '(')
		arithmetic_expansion(buffer, input, f_params);
	else if (*(input->str) == '(')
		substitution_case(buffer, input, f_params, ')');
	else
		variable_expansion(buffer, input, f_params);
	f_params[0] = 1;
	return (0);
}

/*
** Case where a word begins by #
*/

int	comment_input(t_input *input)
{
	while (*(input->str) && *(input->str) != '\n')
		(input->str)++;
	return (0);
}

/*
** Delimiter token found: space or newline
** If there is a previous token, add it in the token list.
*/

int	delimiter_case(t_list **tokens, t_buf *buffer, t_input *input,
		unsigned char f_params[2])
{
	char	*word;

	if (f_params[0] || f_params[1])
	{
		if (!(word = ft_buf_flush(buffer)))
			exit_perror(ENOMEM, NULL);
		insert_token(tokens, word, get_op_type(word));
		f_params[0] = 0;
		f_params[1] = 0;
	}
	if (*(input->str) == '\n')
	{
		if (!(word = ft_strdup("newline")))
			exit_perror(ENOMEM, NULL);
		insert_token(tokens, word, NEWLINE);
	}
	(input->str)++;
	return (0);
}

/*
** Add the current char into the current token buf
*/

int	add_char_to_token(t_buf *buffer, t_input *input)
{
	if (ft_buf_add_char(buffer, *(input->str)) == -1)
		exit_perror(ENOMEM, NULL);
	(input->str)++;
	return (0);
}

/*
** Add the current char into the new token buf.
*/

int	add_char_new_token(t_buf *buffer, t_input *input, unsigned char f_params[2])
{
	if (ft_buf_add_char(buffer, *(input->str)) == -1)
		exit_perror(ENOMEM, NULL);
	f_params[0] = 1;
	(input->str)++;
	return (0);
}
