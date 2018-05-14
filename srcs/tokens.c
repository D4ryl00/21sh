/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbero <rbarbero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/25 17:09:45 by rbarbero          #+#    #+#             */
/*   Updated: 2018/05/14 18:58:54 by rbarbero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"
#include "libft.h"
#include <stdlib.h>

static void		dollar_input(t_buf *buffer, t_input *input, unsigned char f_params[3]);

static int	insert_token(t_list **tokens, char *token)
{
	t_list	*tmp;

	if (!token || !(tmp = (t_list *)malloc(sizeof(t_list))))
		return (return_perror(ENOMEM, NULL));
	tmp->content = (void *)token;
	tmp->content_size = ft_strlen(token) + 1;
	tmp->next = NULL;
	ft_lstaddback(tokens, tmp);
	return (1);
}

static int is_op(t_buf *buffer, char c)
{
	int	i;

	i = -1;
	while (*g_op_token[++i])
	{
		if (*(buffer->buf) && !ft_strncmp(g_op_token[i], buffer->buf, buffer->i)
				&& g_op_token[i][buffer->i] == c)
			return (1);
		else if (!*(buffer->buf) && c == g_op_token[i][0])
			return (1);
	}
	return (0);
}

static void		sq_input(t_buf *buffer, t_input *input
		, unsigned char f_params[3])
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
}

static void		bs_input(t_buf *buffer, t_input *input
		, unsigned char f_params[3])
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
}

static void		bq_input(t_buf *buffer, t_input *input
		, unsigned char f_params[3])
{
	ft_buf_add_char(buffer, *(input->str));
	(input->str)++;
	if (*(input->str))
	{
		ft_buf_add_char(buffer, *(input->str));
		(input->str)++;
	}
	f_params[0] = 1;
}

static void		dq_input(t_buf *buffer, t_input *input
		, unsigned char f_params[3])
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
			bq_input(buffer, input, f_params);
		else if (*(input->str) == '$')
			dollar_input(buffer, input, f_params);
		else
		{
			ft_buf_add_char(buffer, *(input->str));
			(input->str)++;
		}
	}
	ft_buf_add_char(buffer, *(input->str));
	(input->str)++;
	f_params[0] = 1;
}

static void		comment_input(t_input *input)
{
	while (*(input->str) && *(input->str) != '\n')
		(input->str)++;
	if (*(input->str))
		(input->str)++;
}

static void		get_token_expansion(t_buf *buffer, t_input *input
		, unsigned char f_params[3])
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
			sq_input(buffer, input, f_params);
		else if (*(input->str) == '"')
			dq_input(buffer, input, f_params);
		else if (*(input->str) == '\\')
			bq_input(buffer, input, f_params);
		else
		{
			ft_buf_add_char(buffer, *(input->str));
			(input->str)++;
		}
	}
	ft_buf_add_char(buffer, *(input->str));
	(input->str)++;
}

static void		get_token_arithmetic(t_buf *buffer, t_input *input
		, unsigned char f_params[3])
{
	(void)buffer;
	(void)input;
	(void)f_params;
}

static void		get_token_substitution(t_buf *buffer, t_input *input
		, unsigned char f_params[3], char close)
{
	(void)buffer;
	(void)input;
	(void)f_params;
	(void)close;
}

static void		dollar_input(t_buf *buffer, t_input *input
		, unsigned char f_params[3])
{
	ft_buf_add_char(buffer, *(input->str));
	(input->str)++;
	if (*(input->str) == '{')
		get_token_expansion(buffer, input, f_params);
	else if (*(input->str) == '(' && input->str[1] == '(')
		get_token_arithmetic(buffer, input, f_params);
	else if (*(input->str) == '(')
		get_token_substitution(buffer, input, f_params, ')');
	f_params[0] = 1;
}

static int		get_token_loop(t_list **tokens, t_input *input
		, t_buf *buffer, unsigned char f_params[3])
{
	while (*(input->str))
	{
		if (f_params[1])
		{
			if (is_op(buffer, *(input->str)))
			{
				
				if (!ft_buf_add_char(buffer, *(input->str)))
					return (return_perror(ENOMEM, NULL));
			}
			else
			{
				if (!insert_token(tokens, ft_buf_flush(buffer))
						|| ft_buf_add_char(buffer, *(input->str)))
					return (return_perror(ENOMEM, NULL));
				f_params[0] = 1;
				f_params[1] = 0;
				(input->str)++;
			}
			(input->str)++;
		}
		else if (*(input->str) == '\'')
			sq_input(buffer, input, f_params);
		else if (*(input->str) == '"')
			dq_input(buffer, input, f_params);
		else if (*(input->str) == '\\')
			bs_input(buffer, input, f_params);
		else if (*(input->str) == '$')
			dollar_input(buffer, input, f_params);
		else if (*(input->str) == '`')
			get_token_substitution(buffer, input, f_params, '`');
		else if (is_op(buffer, *(input->str)) && f_params[0])
		{
			if (!insert_token(tokens, ft_buf_flush(buffer))
					|| ft_buf_add_char(buffer, *(input->str)))
				return (return_perror(ENOMEM, NULL));
			f_params[0] = 0;
			f_params[1] = 1;
			(input->str)++;
		}
		else if (*(input->str) == ' ')
		{
			if (f_params[0] || f_params[1])
			{
				if (!insert_token(tokens, ft_buf_flush(buffer)))
					return (return_perror(ENOMEM, NULL));
				f_params[0] = 0;
				f_params[1] = 0;
			}
			(input->str)++;
		}
		else if (f_params[0])
		{
			if (!ft_buf_add_char(buffer, *(input->str)))
				return (return_perror(ENOMEM, NULL));
			(input->str)++;
		}
		else if (*(input->str) == '#')
			comment_input(input);
		else
		{
			if (!ft_buf_add_char(buffer, *(input->str)))
				return (return_perror(ENOMEM, NULL));
			f_params[0] = 1;
			(input->str)++;
		}
	}
	if (f_params[0] || f_params[1])
	{
		if (!insert_token(tokens, ft_buf_flush(buffer)))
				return (return_perror(ENOMEM, NULL));
	}
	return (1);
}

void	token_free(void *content, size_t size)
{
	(void)size;
	if (content)
		free(content);
}

/*
** f_params[3]: flags while parsing the input
** 1: is reading a token;
** 2: is reading a operator token;
** 3: is quoted.
*/

t_list	*get_tokens(t_input *input)
{
	t_list			*tokens;
	unsigned char	f_params[3];
	t_buf			buffer;

	tokens = NULL;
	if (!ft_buf_init(&buffer))
		exit_perror(ENOMEM, NULL);
	f_params[0] = 0;
	f_params[1] = 0;
	f_params[2] = 0;
	if (!get_token_loop(&tokens, input, &buffer, f_params))
	{
		ft_lstdel(&tokens, token_free);
		ft_buf_destroy(&buffer);
		return (NULL);
	}
	ft_buf_destroy(&buffer);
	return (tokens);
}
