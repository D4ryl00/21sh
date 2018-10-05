/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbero <rbarbero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/25 17:09:45 by rbarbero          #+#    #+#             */
/*   Updated: 2018/10/05 22:32:27 by rbarbero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"
#include "libft.h"
#include <stdlib.h>

int				is_operator(t_buf *buffer, char c, unsigned char f_params[2])
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

void			insert_token(t_list **tokens, char *token, enum e_token type)
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

static int		get_token_loop(t_list **tokens, t_input *input
		, t_buf *buffer, unsigned char f_params[2])
{
	int		ret;

	while (*(input->str))
	{
		if (f_params[1])
			ret = operator_case(tokens, buffer, input, f_params);
		else if (*(input->str) == '\'')
			ret = sq_case(buffer, input, f_params);
		else if (*(input->str) == '"')
			ret = dq_case(buffer, input, f_params);
		else if (*(input->str) == '\\')
			ret = bs_case(buffer, input, f_params);
		else if (*(input->str) == '$')
			ret = dollar_case(buffer, input, f_params);
		else if (*(input->str) == '`')
			ret = substitution_case(buffer, input, f_params, '`');
		else if (is_operator(buffer, *(input->str), f_params))
			ret = operator_start_case(tokens, buffer, input, f_params);
		else if ((*(input->str) == ' ') || (*(input->str) == '\n'))
			ret = delimiter_case(tokens, buffer, input, f_params);
		else if (f_params[0])
			ret = word_add_char_case(buffer, input);
		else if (*(input->str) == '#')
			ret = comment_input(input);
		else
			ret = word_start_case(buffer, input, f_params);
		if (ret == -1)
			return (return_perror(ENOMEM, NULL));
	}
	return (0);
}

/*
** f_params[2]: flags while parsing the input
** 1: is reading a token;
** 2: is reading a operator token;
*/

t_list	*get_tokens(t_input *input)
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
	if (get_token_loop(&tokens, input, &buffer, f_params) == -1)
	{
		ft_lstdel(&tokens, token_free);
		tokens = NULL;
	}
	if (f_params[0] || f_params[1])
	{
		if (!(word = ft_buf_flush(&buffer)))
			exit_perror(ENOMEM, NULL);
		insert_token(&tokens, word, token_get_op_type(word));
	}
	ft_buf_destroy(&buffer);
	return (tokens);
}
