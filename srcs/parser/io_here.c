/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io_here.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbero <rbarbero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/05 07:47:05 by rbarbero          #+#    #+#             */
/*   Updated: 2019/10/15 11:21:51 by rbarbero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "sh.h"
#include "parser.h"

/*
** Remove newline and compare with end word.
*/

static int	is_end_word(char *input, const char *end_word)
{
	int		status;
	char	tmp;
	size_t	len;

	status = 0;
	len = ft_strlen(input);
	tmp = input[len - 1];
	input[len - 1] = '\0';
	if (!ft_strcmp(input, end_word))
		status = 1;
	input[len - 1] = tmp;
	return (status);
}

/*
** if newprompt catch ctrl+c or an error, return -2 because -1 is an
** invalid syntax error.
*/

static int	here_loop(t_ast_io_here *here)
{
	int		status;
	t_input	input;
	t_buf	buffer;

	input.save = NULL;
	if (ft_buf_init(&buffer) == -1)
		exit_perror(ENOMEM, NULL);
	while (((status = newprompt(&input, "> ")) != -1)
			&& !is_end_word(input.str, here->here_end->word))
	{
		if (ft_buf_add_nstr(&buffer, input.str, ft_strlen(input.str)) == -1)
			exit_perror(ENOMEM, NULL);
		free(input.save);
		input.save = NULL;
	}
	if (status != -1)
	{
		here->data_len = buffer.i;
		if (!(here->data = ft_buf_flush(&buffer)))
			exit_perror(ENOMEM, NULL);
	}
	if (input.save)
		free(input.save);
	ft_buf_destroy(&buffer);
	return (status == -1 ? -2 : 0);
}

static void	io_here_init(t_ast_io_here *here)
{
	here->here_end = NULL;
	here->data = NULL;
	here->data_len = 0;
	here->op = TOKEN;
}

int			ast_io_here(t_ast_io_here **here, t_list **tokens)
{
	int	status;

	status = 0;
	if (*tokens)
	{
		if (!(*here = (t_ast_io_here *)malloc(sizeof(t_ast_io_here))))
			exit_perror(ENOMEM, NULL);
		io_here_init(*here);
		if (((t_token *)(*tokens)->content)->type == DLESS
				|| ((t_token *)(*tokens)->content)->type == DLESSDASH)
		{
			(*here)->op = ((t_token *)(*tokens)->content)->type;
			*tokens = (*tokens)->next;
			status = ast_here_end(&((*here)->here_end), tokens);
		}
		if ((status < 1) || ((status = here_loop(*here)) == -2))
		{
			free_ast_io_here(*here);
			*here = NULL;
			return (status);
		}
		return (1);
	}
	return (0);
}

void		free_ast_io_here(t_ast_io_here *io_here)
{
	if (io_here)
	{
		if (io_here->here_end)
			free_ast_here_end(io_here->here_end);
		if (io_here->data)
			free(io_here->data);
		free(io_here);
	}
}
