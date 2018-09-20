/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_free.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbero <rbarbero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/13 00:06:28 by rbarbero          #+#    #+#             */
/*   Updated: 2018/09/20 16:45:15 by rbarbero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"
#include <stdlib.h>

void	free_ast_filename(t_ast_filename *filename)
{
	if (filename)
	{
		free(filename->word);
		free(filename);
	}
}

void	free_ast_io_file(t_ast_io_file *file)
{
	if (file)
	{
		if (file->filename)
		{
			free_ast_filename(file->filename);
			file->filename = NULL;
		}
		if (file->op)
		{
			free(file->op);
			file->op = NULL;
		}
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
		if (io_here->op)
		{
			free(io_here->op);
			io_here->op = NULL;
		}
		if (io_here->here_end)
		{
			free_ast_here_end(io_here->here_end);
			io_here->here_end = NULL;
		}
		free(io_here);
	}
}

void	free_ast_io_redirect(t_ast_io_redirect *redirect)
{
	if (redirect)
	{
		if (redirect->io_file)
		{
			free_ast_io_file(redirect->io_file);
			redirect->io_file = NULL;
		}
		if (redirect->io_here)
		{
			free_ast_io_here(redirect->io_here);
			redirect->io_here = NULL;
		}
		free(redirect);
	}
}

void	free_ast_cmd_suffix(t_ast_cmd_suffix * suffix)
{
	if (suffix)
	{
		if (suffix->io_redirect)
		{
			free_ast_io_redirect(suffix->io_redirect);
			suffix->io_redirect = NULL;
		}
		if (suffix->word)
		{
			free(suffix->word);
			suffix->word = NULL;
		}
		if (suffix->cmd_suffix)
		{
			free_ast_cmd_suffix(suffix->cmd_suffix);
			suffix->cmd_suffix = NULL;
		}
		free(suffix);
	}
}

void	free_ast_cmd_name(t_ast_cmd_name *cmd_name)
{
	if (cmd_name)
	{
		if (cmd_name->word)
		{
			free(cmd_name->word);
			cmd_name->word = NULL;
		}
	}
}

void	free_ast_simple_command(t_ast_simple_command *sc)
{
	if (sc)
	{
		if (sc->cmd_name)
		{
			free_ast_cmd_name(sc->cmd_name);
			sc->cmd_name = NULL;
		}
		if (sc->cmd_suffix)
		{
			free_ast_cmd_suffix(sc->cmd_suffix);
			sc->cmd_suffix = NULL;
		}
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
		{
			free_ast_io_redirect(rl->io_redirect);
			rl->io_redirect = NULL;
		}
		free(rl);
	}
}

void	free_ast_command(t_ast_command *command)
{
	if (command)
	{
		if (command->simple_command)
		{
			free_ast_simple_command(command->simple_command);
			command->simple_command = NULL;
		}
		if (command->redirect_list)
		{
			free_ast_redirect_list(command->redirect_list);
			command->redirect_list = NULL;
		}
		free(command);
	}
}

void	free_ast_program(t_ast_program *program)
{
	if (program)
	{
		if (program->command)
		{
			free_ast_command(program->command);
			program->command = NULL;
		}
		free(program);
	}
}
