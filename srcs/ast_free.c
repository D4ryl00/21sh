/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_free.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbero <rbarbero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/13 00:06:28 by rbarbero          #+#    #+#             */
/*   Updated: 2018/10/02 16:34:29 by rbarbero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"
#include <stdlib.h>

void	free_ast_filename(t_ast_filename *filename)
{
	if (filename)
	{
		if (filename->word)
			free(filename->word);
		free(filename);
	}
}

void	free_ast_io_file(t_ast_io_file *file)
{
	if (file)
	{
		if (file->filename)
			free_ast_filename(file->filename);
		if (file->op)
			free(file->op);
		free(file);
	}
}

void	free_ast_here_end(t_ast_here_end *here_end)
{
	if (here_end)
	{
		if (here_end->word)
			free(here_end->word);
		free(here_end);
	}
}

void	free_ast_io_here(t_ast_io_here *io_here)
{
	if (io_here)
	{
		if (io_here->here_end)
			free_ast_here_end(io_here->here_end);
		free(io_here);
	}
}

void	free_ast_io_redirect(t_ast_io_redirect *redirect)
{
	if (redirect)
	{
		if (redirect->io_file)
			free_ast_io_file(redirect->io_file);
		if (redirect->io_here)
			free_ast_io_here(redirect->io_here);
		free(redirect);
	}
}

void	free_ast_cmd_suffix(t_ast_cmd_suffix *suffix)
{
	if (suffix)
	{
		if (suffix->io_redirect)
			free_ast_io_redirect(suffix->io_redirect);
		if (suffix->word)
			free(suffix->word);
		if (suffix->cmd_suffix)
			free_ast_cmd_suffix(suffix->cmd_suffix);
		free(suffix);
	}
}

void	free_ast_cmd_prefix(t_ast_cmd_prefix *prefix)
{
	if (prefix)
	{
		if (prefix->io_redirect)
			free_ast_io_redirect(prefix->io_redirect);
		if (prefix->assignment_word)
			free(prefix->assignment_word);
		if (prefix->cmd_prefix)
			free_ast_cmd_prefix(prefix->cmd_prefix);
		free(prefix);
	}
}

void	free_ast_cmd_word(t_ast_cmd_word *cmd_word)
{
	if (cmd_word)
	{
		if (cmd_word->word)
			free(cmd_word->word);
		free(cmd_word);
	}
}

void	free_ast_cmd_name(t_ast_cmd_name *cmd_name)
{
	if (cmd_name)
	{
		if (cmd_name->word)
			free(cmd_name->word);
		free(cmd_name);
	}
}

void	free_ast_simple_command(t_ast_simple_command *sc)
{
	if (sc)
	{
		if (sc->cmd_prefix)
			free_ast_cmd_prefix(sc->cmd_prefix);
		if (sc->cmd_word)
			free_ast_cmd_word(sc->cmd_word);
		if (sc->cmd_name)
			free_ast_cmd_name(sc->cmd_name);
		if (sc->cmd_suffix)
			free_ast_cmd_suffix(sc->cmd_suffix);
		free(sc);
	}
}

void	free_ast_redirect_list(t_ast_redirect_list *rl)
{
	if (rl)
	{
		if (rl->redirect_list)
		{
		}
		if (rl->io_redirect)
			free_ast_io_redirect(rl->io_redirect);
		free(rl);
	}
}

void	free_ast_command(t_ast_command *command)
{
	if (command)
	{
		if (command->simple_command)
			free_ast_simple_command(command->simple_command);
		if (command->redirect_list)
			free_ast_redirect_list(command->redirect_list);
		free(command);
	}
}

void	free_ast_newline_list(t_ast_newline_list* newline_list)
{
	if (newline_list)
	{
		if (newline_list->newline_list)
			free_ast_newline_list(newline_list->newline_list);
		free(newline_list);
	}
}

void	free_ast_linebreak(t_ast_linebreak *linebreak)
{
	if (linebreak)
	{
		if (linebreak->newline_list)
			free_ast_newline_list(linebreak->newline_list);
		free(linebreak);
	}
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

void	free_ast_pipeline(t_ast_pipeline *pipeline)
{
	if (pipeline)
	{
		if (pipeline->pipe_sequence)
			free_ast_pipe_sequence(pipeline->pipe_sequence);
		free(pipeline);
	}
}

void	free_ast_and_or(t_ast_and_or *and_or)
{
	if (and_or)
	{
		if (and_or->pipeline)
			free_ast_pipeline(and_or->pipeline);
		if (and_or->linebreak)
			free_ast_linebreak(and_or->linebreak);
		if (and_or->and_or)
			free_ast_and_or(and_or->and_or);
		free(and_or);
	}
}

void	free_ast_separator_op(t_ast_separator_op *s_op)
{
	if (s_op)
	{
		free(s_op);
	}
}

void	free_ast_list(t_ast_list *list)
{
	if (list)
	{
		if (list->and_or)
			free_ast_and_or(list->and_or);
		if (list->separator_op)
			free_ast_separator_op(list->separator_op);
		if (list->list)
			free_ast_list(list->list);
		free(list);
	}
}

void	free_ast_complete_command(t_ast_complete_command* cc)
{
	if (cc)
	{
		if (cc->list)
			free_ast_list(cc->list);
		if (cc->separator_op)
			free_ast_separator_op(cc->separator_op);
		free(cc);
	}
}

void	free_ast_complete_commands(t_ast_complete_commands *cc)
{
	if (cc)
	{
		if (cc->complete_command)
			free_ast_complete_command(cc->complete_command);
		if (cc->newline_list)
			free_ast_newline_list(cc->newline_list);
		if (cc->complete_commands)
			free_ast_complete_commands(cc->complete_commands);
		free(cc);
	}
}

void	free_ast_program(t_ast_program *program)
{
	if (program)
	{
		if (program->linebreak)
			free_ast_linebreak(program->linebreak);
		if (program->complete_commands)
			free_ast_complete_commands(program->complete_commands);
		if (program->post_linebreak)
			free_ast_linebreak(program->post_linebreak);
		free(program);
	}
}
