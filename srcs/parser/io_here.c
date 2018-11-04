/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io_here.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbero <rbarbero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/05 07:47:05 by rbarbero          #+#    #+#             */
/*   Updated: 2018/11/04 16:46:50 by rbarbero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "sh.h"
#include "parser.h"

static int	here_loop(t_ast_io_here *here)
{
	int		status;
	t_input	input;
	int		len;
	t_buf	buffer;

	status = 0;
	input.save = NULL;
	if (ft_buf_init(&buffer) == -1)
		exit_perror(ENOMEM, NULL);
	while ((status = newprompt(&input, "> ") != -1)
			&& (((len = ft_strlen(input.str)) == 1) || ft_strncmp(input.str
				, here->here_end->word, len - 1)))
	{
		if (ft_buf_add_nstr(&buffer, input.str, len) == -1)
			exit_perror(ENOMEM, NULL);
		free(input.save);
		input.save = NULL;
	}
	here->data_len = buffer.i;
	if (!(here->data = ft_buf_flush(&buffer)))
		exit_perror(ENOMEM, NULL);
	if (input.save)
		free(input.save);
	ft_buf_destroy(&buffer);
	return (status);
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
		if (status < 1)
		{
			free_ast_io_here(*here);
			*here = NULL;
			return (status);
		}
		here_loop(*here);
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
