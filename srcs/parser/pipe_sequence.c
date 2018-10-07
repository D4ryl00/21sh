/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_sequence.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbero <rbarbero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/05 08:05:34 by rbarbero          #+#    #+#             */
/*   Updated: 2018/10/07 12:14:58 by rbarbero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "sh.h"
#include "parser.h"

int		ast_pipe_sequence(t_ast_pipe_sequence **ps, t_list **tokens)
{
	int		status;
	t_list	*save;

	save = *tokens;
	if (*tokens)
	{
		if (!(*ps = (t_ast_pipe_sequence *)malloc(sizeof(t_ast_pipe_sequence))))
			exit_perror(ENOMEM, NULL);
		(*ps)->command = NULL;
		(*ps)->linebreak = NULL;
		(*ps)->pipe_sequence = NULL;
		if ((status = ast_command(&((*ps)->command), tokens)) > 0)
		{
			if (*tokens && !ft_strcmp(((t_token *)(*tokens)->content)
						->content, "|"))
			{
				*tokens = (*tokens)->next;
				ast_linebreak(&((*ps)->linebreak), tokens);
				if (!*tokens && get_new_tokens(tokens, save) == -1)
					return (-1);
				if ((status = ast_pipe_sequence(&((*ps)->pipe_sequence), tokens)) < 1)
				{
					free_ast_pipe_sequence(*ps);
					*ps = NULL;
					return (status);
				}
			}
		}
		else
		{
			free_ast_pipe_sequence(*ps);
			*ps = NULL;
			return (status);
		}
		return (1);
	}
	return (0);
}

void	free_ast_pipe_sequence(t_ast_pipe_sequence *ps)
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
