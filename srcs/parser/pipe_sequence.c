/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_sequence.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbero <rbarbero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/05 08:05:34 by rbarbero          #+#    #+#             */
/*   Updated: 2018/11/04 13:29:39 by rbarbero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "sh.h"
#include "parser.h"

/*
** Init a t_ast_pipe_sequence with default values.
*/

static void	pipe_sequence_init(t_ast_pipe_sequence *ps)
{
	if (ps)
	{
		ps->command = NULL;
		ps->linebreak = NULL;
		ps->pipe_sequence = NULL;
	}
}

/*
** Free the whole structure
*/

void		free_ast_pipe_sequence(t_ast_pipe_sequence *ps)
{
	if (ps)
	{
		if (ps->linebreak)
			free_ast_linebreak(ps->linebreak);
		if (ps->command)
			free_ast_command(ps->command);
		if (ps->pipe_sequence)
			free_ast_pipe_sequence(ps->pipe_sequence);
		free(ps);
	}
}

/*
** Free the ast_and_or struct and set the pointer NULL.
*/

static int	ast_pipe_sequence_error(t_ast_pipe_sequence **ps, int status)
{
	if (ps && *ps)
	{
		free_ast_pipe_sequence(*ps);
		*ps = NULL;
	}
	return (status);
}

/*
** It's called when the input line contain a pipe.
** Evaluate the 2nd part of the operator.
** Call a new prompt if needed.
*/

static int	ast_pipe_sequence_next(t_ast_pipe_sequence **ps, t_list **tokens
		, t_list *save)
{
	int	status;

	status = 1;
	*tokens = (*tokens)->next;
	ast_linebreak(&((*ps)->linebreak), tokens);
	while (!*tokens)
	{
		if (!*tokens && get_new_tokens(tokens, save) == -1)
			return (-1);
		ast_linebreak(&((*ps)->linebreak), tokens);
	}
	if ((status = ast_pipe_sequence(&((*ps)->pipe_sequence), tokens)) < 1)
		return (ast_pipe_sequence_error(ps, status));
	return (status);
}

/*
** Pipe sequence (see shell grammar).
*/

int			ast_pipe_sequence(t_ast_pipe_sequence **ps, t_list **tokens)
{
	int		status;
	t_list	*save;

	save = *tokens;
	if (*tokens)
	{
		if (!(*ps = (t_ast_pipe_sequence *)malloc(sizeof(t_ast_pipe_sequence))))
			exit_perror(ENOMEM, NULL);
		pipe_sequence_init(*ps);
		if ((status = ast_command(&((*ps)->command), tokens)) > 0)
		{
			if (*tokens && ((t_token *)(*tokens)->content)->type == PIPE)
				if ((status = ast_pipe_sequence_next(ps, tokens, save)) < 1)
					return (status);
		}
		else
			return (ast_pipe_sequence_error(ps, status));
		return (1);
	}
	return (0);
}
