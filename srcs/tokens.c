/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbero <rbarbero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/25 17:09:45 by rbarbero          #+#    #+#             */
/*   Updated: 2018/05/18 11:38:12 by rbarbero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"
#include "libft.h"
#include <stdlib.h>

int	dollar_case(t_buf *buffer, t_input *input, unsigned char f_params[2]);

static int	insert_token(t_list **tokens, char *token
		, unsigned char f_params[2])
{
	t_list	*tmp;

	if (!token || !(tmp = (t_list *)malloc(sizeof(t_list))))
		return (return_perror(ENOMEM, NULL));
	if (!(tmp->content = (t_token *)malloc(sizeof(t_token))))
		return (return_perror(ENOMEM, NULL));
	((t_token *)tmp->content)->content = token;
	((t_token *)tmp->content)->type = f_params[0] ? WORD : OPERATOR;
	tmp->content_size = sizeof(t_token);
	tmp->next = NULL;
	ft_lstaddback(tokens, tmp);
	return (0);
}

static int is_operator(t_buf *buffer, char c, unsigned char f_params[2])
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

int	sq_case(t_buf *buffer, t_input *input
		, unsigned char f_params[2])
{
	ft_buf_add_char(buffer, *(input->str));
	(input->str)++;
	while (1)
	{
		if (!*(input->str))
		{
			free(input->save);
			if (!newprompt(input, "> "))
				exit_perror(EOTHER, "syntax error");
		}
		else if (*(input->str) == '\'')
			break ;
		else
		{
			ft_buf_add_char(buffer, *(input->str));
			(input->str)++;
		}
	}
	ft_buf_add_char(buffer, *(input->str));
	(input->str)++;
	f_params[0] = 1;
	return (0);
}

int	bs_case(t_buf *buffer, t_input *input
		, unsigned char f_params[2])
{
	ft_buf_add_char(buffer, *(input->str));
	(input->str)++;
	if (!*(input->str))
	{
		free(input->save);
		if (!newprompt(input, "> "))
			exit_perror(EOTHER, "syntax error");
	}
	if (*(input->str))
	{
		ft_buf_add_char(buffer, *(input->str));
		(input->str)++;
		f_params[0] = 1;
	}
	return (0);
}

int	bq_input(t_buf *buffer, t_input *input
		, unsigned char f_params[2])
{
	ft_buf_add_char(buffer, *(input->str));
	(input->str)++;
	if (*(input->str))
	{
		ft_buf_add_char(buffer, *(input->str));
		(input->str)++;
	}
	f_params[0] = 1;
	return (0);
}

int	dq_case(t_buf *buffer, t_input *input
		, unsigned char f_params[2])
{
	ft_buf_add_char(buffer, *(input->str));
	(input->str)++;
	while (1)
	{
		if (!*(input->str))
		{
			free(input->save);
			if (!newprompt(input, "> "))
				exit_perror(EOTHER, "syntax error");
		}
		if (*(input->str) == '"')
			break ;
		else if (*(input->str) == '\\')
			bs_case(buffer, input, f_params);
		else if (*(input->str) == '$')
			dollar_case(buffer, input, f_params);
		else
		{
			ft_buf_add_char(buffer, *(input->str));
			(input->str)++;
		}
	}
	ft_buf_add_char(buffer, *(input->str));
	(input->str)++;
	f_params[0] = 1;
	return (0);
}

int	comment_input(t_input *input)
{
	while (*(input->str) && *(input->str) != '\n')
		(input->str)++;
	if (*(input->str))
		(input->str)++;
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
				exit_perror(EOTHER, "syntax error");
		}
		if (*(input->str) == '}')
			break ;
		else if (*(input->str) == '\'')
			sq_case(buffer, input, f_params);
		else if (*(input->str) == '"')
			dq_case(buffer, input, f_params);
		else if (*(input->str) == '\\')
			bs_case(buffer, input, f_params);
		else
		{
			ft_buf_add_char(buffer, *(input->str));
			(input->str)++;
		}
	}
	ft_buf_add_char(buffer, *(input->str));
	(input->str)++;
	return (0);
}

int	get_token_arithmetic(t_buf *buffer, t_input *input
		, unsigned char f_params[2])
{
	int	parenthesis;

	parenthesis = 2;
	while (42)
	{
		if (!*(input->str))
		{
			free(input->save);
			if (!newprompt(input, "> "))
				exit_perror(EOTHER, "syntax error");
		}
		if (*(input->str) == ')' && !(--parenthesis))
			break ;
		else if (*(input->str) == '\'')
			sq_case(buffer, input, f_params);
		else if (*(input->str) == '"')
			dq_case(buffer, input, f_params);
		else if (*(input->str) == '\\')
			bs_case(buffer, input, f_params);
		else
		{
			ft_buf_add_char(buffer, *(input->str));
			(input->str)++;
		}
	}
	ft_buf_add_char(buffer, *(input->str));
	(input->str)++;
	return (0);
}

int	substitution_case(t_buf *buffer, t_input *input
		, unsigned char f_params[2], char close)
{
	while (42)
	{
		if (!*(input->str))
		{
			free(input->save);
			if (!newprompt(input, "> "))
				exit_perror(EOTHER, "syntax error");
		}
		if (*(input->str) == close)
			break ;
		else if (*(input->str) == '\'')
			sq_case(buffer, input, f_params);
		else if (*(input->str) == '"')
			dq_case(buffer, input, f_params);
		else if (*(input->str) == '\\')
			bs_case(buffer, input, f_params);
		else if (*(input->str) == '$')
			dollar_case(buffer, input, f_params);
		else if (*(input->str) == '`')
			bq_input(buffer, input, f_params);
		else
		{
			ft_buf_add_char(buffer, *(input->str));
			(input->str)++;
		}
	}
	ft_buf_add_char(buffer, *(input->str));
	(input->str)++;
	return (0);
}

int	dollar_case(t_buf *buffer, t_input *input
		, unsigned char f_params[2])
{
	ft_buf_add_char(buffer, *(input->str));
	(input->str)++;
	if (*(input->str) == '{')
		get_token_expansion(buffer, input, f_params);
	else if (*(input->str) == '(' && input->str[1] == '(')
		get_token_arithmetic(buffer, input, f_params);
	else if (*(input->str) == '(')
		substitution_case(buffer, input, f_params, ')');
	f_params[0] = 1;
	return (0);
}

int	operator_case(t_list **tokens, t_buf *buffer, t_input *input,
		unsigned char f_params[2])
{
	if (!is_operator(buffer, *(input->str), f_params))
	{
		if (insert_token(tokens, ft_buf_flush(buffer), f_params) == -1)
			return (return_perror(ENOMEM, NULL));
		f_params[0] = 1;
		f_params[1] = 0;
	}
	if (ft_buf_add_char(buffer, *(input->str)) == -1)
		return (return_perror(ENOMEM, NULL));
	(input->str)++;
	return (0);
}

int	operator_start_case(t_list **tokens, t_buf *buffer, t_input *input,
		unsigned char f_params[2])
{
	if (f_params[0] && insert_token(tokens
				, ft_buf_flush(buffer), f_params) == -1)
			return (return_perror(ENOMEM, NULL));
	if (ft_buf_add_char(buffer, *(input->str)) == -1)
		return (return_perror(ENOMEM, NULL));
	f_params[0] = 0;
	f_params[1] = 1;
	(input->str)++;
	return (0);
}

int	delimiter_case(t_list **tokens, t_buf *buffer, t_input *input,
		unsigned char f_params[2])
{
	if (f_params[0] || f_params[1])
	{
		if (insert_token(tokens, ft_buf_flush(buffer), f_params) == -1)
			return (return_perror(ENOMEM, NULL));
		f_params[0] = 0;
		f_params[1] = 0;
	}
	(input->str)++;
	return (0);
}

int	word_add_char_case(t_buf *buffer, t_input *input)
{
	if (ft_buf_add_char(buffer, *(input->str)) == -1)
		return (return_perror(ENOMEM, NULL));
	(input->str)++;
	return (0);
}

int	word_start_case(t_buf *buffer, t_input *input, unsigned char f_params[2])
{
	if (ft_buf_add_char(buffer, *(input->str)) == -1)
		return (return_perror(ENOMEM, NULL));
	f_params[0] = 1;
	(input->str)++;
	return (0);
}

static int		get_token_loop(t_list **tokens, t_input *input
		, t_buf *buffer, unsigned char f_params[2])
{
	int	ret;

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
		else if (*(input->str) == ' ')
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
	if (f_params[0] || f_params[1])
	{
		if (insert_token(tokens, ft_buf_flush(buffer), f_params) == -1)
			return (return_perror(ENOMEM, NULL));
	}
	return (0);
}

void	token_free(void *content, size_t size)
{
	(void)size;
	if (content)
	{
		if (((t_token *)content)->content)
			free(((t_token *)content)->content);
		free(content);
	}
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

	tokens = NULL;
	if (ft_buf_init(&buffer) == -1)
		exit_perror(ENOMEM, NULL);
	f_params[0] = 0;
	f_params[1] = 0;
	if (get_token_loop(&tokens, input, &buffer, f_params) == -1)
	{
		ft_lstdel(&tokens, token_free);
		ft_buf_destroy(&buffer);
		return (NULL);
	}
	ft_buf_destroy(&buffer);
	return (tokens);
}
