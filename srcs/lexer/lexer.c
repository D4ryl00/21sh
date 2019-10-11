/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbero <rbarbero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/05 22:57:48 by rbarbero          #+#    #+#             */
/*   Updated: 2019/10/11 17:52:04 by rbarbero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "sh.h"
#include "lexer.h"
#include <stdlib.h>

/*
** Return true if the token is an operator (see g_op_token)
*/

int			is_operator(t_buf *buffer, char c, unsigned char f_params[2])
{
	int	i;

	i = -1;
	while (*g_op_token[++i])
	{
		if (f_params[0])
		{
			if (c == g_op_token[i][0])
				return (1);
		}
		else
		{
			if (buffer->i && !ft_strncmp(g_op_token[i], buffer->buf, buffer->i)
					&& g_op_token[i][buffer->i] == c)
				return (1);
			else if (!(buffer->i) && c == g_op_token[i][0])
				return (1);
		}
	}
	return (0);
}

/*
** Insert a new token in a token list.
*/

void		insert_token(t_list **tokens, char *token, enum e_token type)
{
	t_list	*tmp;

	if (!(tmp = (t_list *)malloc(sizeof(t_list))))
		exit_perror(ENOMEM, NULL);
	if (!(tmp->content = (t_token *)malloc(sizeof(t_token))))
		exit_perror(ENOMEM, NULL);
	((t_token *)tmp->content)->content = token;
	((t_token *)tmp->content)->type = type;
	tmp->content_size = sizeof(t_token);
	tmp->next = NULL;
	ft_lstaddback(tokens, tmp);
}

static int	char_cases(t_list **tokens, t_input *input
		, t_buf *buffer, unsigned char f_params[2])
{
	int	status;

	if (f_params[1])
		status = operator_case(tokens, buffer, input, f_params);
	else if (*(input->str) == '\'')
		status = sq_case(buffer, input, f_params);
	else if (*(input->str) == '"')
		status = dq_case(buffer, input, f_params);
	else if (*(input->str) == '\\')
		status = bs_case(buffer, input, f_params);
	else if (*(input->str) == '$')
		status = dollar_case(buffer, input, f_params);
	else if (*(input->str) == '`')
		status = substitution_case(buffer, input, f_params, '`');
	else if (is_operator(buffer, *(input->str), f_params))
		status = operator_start_case(tokens, buffer, input, f_params);
	else if (*(input->str) == ' ')
		status = delimiter_case(tokens, buffer, input, f_params);
	else if (f_params[0])
		status = add_char_to_token(buffer, input);
	else if (*(input->str) == '#')
		status = comment_input(input);
	else
		status = add_char_new_token(buffer, input, f_params);
	return (status);
}

/*
** Take each character in a buffer.
** When a token is completed, duplicate it in a token list
** whith its category.
*/

static int	for_each_char(t_list **tokens, t_input *input
		, t_buf *buffer, unsigned char f_params[2])
{
	while (*(input->str))
	{
		if (char_cases(tokens, input, buffer, f_params) == -1)
			return (-1);
	}
	return (0);
}

/*
** Convert string input into tokens.
** f_params[0]: true when reading a token;
** f_params[1]: true when reading a operator token;
*/

t_list		*lexer(t_input *input)
{
	t_list			*tokens;
	unsigned char	f_params[2];
	t_buf			buffer;
	char			*word;

	tokens = NULL;
	if (ft_buf_init(&buffer) == -1)
		exit_perror(ENOMEM, NULL);
	f_params[0] = 0;
	f_params[1] = 0;
	if (!for_each_char(&tokens, input, &buffer, f_params)
			&& (f_params[0] || f_params[1]))
	{
		if (!(word = ft_buf_flush(&buffer)))
			exit_perror(ENOMEM, NULL);
		insert_token(&tokens, word, get_op_type(word));
	}
	ft_buf_destroy(&buffer);
	return (tokens);
}
