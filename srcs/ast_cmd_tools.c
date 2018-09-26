/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_cmd_tools.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbero <rbarbero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/18 14:50:03 by rbarbero          #+#    #+#             */
/*   Updated: 2018/09/27 00:40:59 by rbarbero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"
#include "libft.h"
#include <stdlib.h>

/*
** For open.
*/

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

/*
** For dup
*/

#include <unistd.h>

/*
** For a simple_command, return the number of arguments of the command.
*/

static int	ast_get_cmd_args_size(t_ast_simple_command *sc)
{
	int	size;
	t_ast_cmd_suffix	*suffix;

	size = 0;
	suffix = sc->cmd_suffix;
	while (suffix)
	{
		if (suffix->word)
			size++;
		suffix = suffix->cmd_suffix;
	}
	return (size);
}

/*
** For a simple_command, return an array of string with arguments
** of the command for execve. It's begin by the command name
** and terminate by a NULL pointer.
*/

char	**ast_construct_cmd_args(t_ast_simple_command *sc)
{
	char				**args;
	int					size;
	int					i;
	t_ast_cmd_suffix	*suffix;

	args = NULL;
	size = ast_get_cmd_args_size(sc) + 1;
	if (!(args = (char **)malloc(sizeof(char *) * size + 1)))
		exit_perror(ENOMEM, NULL);
	args[0] = ft_strdup(ast_get_cmd_name(sc));
	i = 1;
	suffix = sc->cmd_suffix;
	while (suffix)
	{
		if (suffix->word)
		{
			if (!(args[i++] = ft_strdup(suffix->word)))
				exit_perror(ENOMEM, NULL);
		}
		suffix = suffix->cmd_suffix;
	}
	args[size] = NULL;
	return (args);
}

/*
** Redirection [n]> or [n]>> into a file,
** where [n] is an optional fd (default 1).
*/

static int	filename_redirect(t_ast_cmd_suffix *suffix, int io_number, char op
		, int mode)
{
	int	fd;

	if (io_number == -1)
		io_number = op == '>' ? 1 : 0;
	if ((fd = open(suffix->io_redirect->io_file->filename->word
		, mode, 0644)) == -1)
		return (return_perror(EOPEN, NULL));
	if (dup2(fd, io_number) == -1)
	{
		close(fd);
		return (return_perror(EDUP, NULL));
	}
	close(fd);
	return (0);
}

/*
** Redirection [n]>& or [n]<& into an other fd,
** where [n] is an optional fd (default 1 for >& and 0 for <&)
*/

static int	fd_redirect(t_ast_cmd_suffix *suffix, int io_number, char op)
{
	if (io_number == -1)
		io_number = op == '>' ? 1 : 0;
	if (ft_isstrdigit(suffix->io_redirect->io_file->filename->word))
	{
		if (dup2(ft_atoi(suffix->io_redirect->io_file->filename->word)
		, io_number) == -1)
			return (return_perror(EDUP, NULL));
	}
	else if (op == '>')
		return (filename_redirect(suffix, io_number, '>', O_CREAT|O_WRONLY));
	else
		return (filename_redirect(suffix, io_number, '<', O_CREAT|O_RDONLY));
	return (0);
}

/*
** For here documents, call the newprompt function until catch the keyword
*/

int	here_redirect(t_ast_cmd_suffix *suffix, int io_number)
{
	t_input	input;
	int		status;
	int		fd_pipe[2];

	io_number = io_number == -1 ? 0 : io_number;
	if (pipe(fd_pipe) == -1)
		return_perror(EPIPE, NULL);
	while ((status = newprompt(&input, "> ") != -1) && ft_strncmp(input.str
				, suffix->io_redirect->io_here->here_end->word
				, ft_strlen(input.str) - 1))
	{
		write(fd_pipe[1], input.str, ft_strlen(input.str));
		close(fd_pipe[1]);
		if (dup2(fd_pipe[0], io_number) == -1)
			return_perror(EDUP, NULL);
		free(input.save);
		input.save = NULL;
		input.str = NULL;
	}
	if (status == -1)
		exit_perror(ENOMEM, NULL);
	if (input.save)
		free(input.save);
	return (0);
}

/*
** Scan a simple_command and get input and output redirections if they exist.
** Set the address of the structures in the args.
*/

int	cmd_ast_eval_redirs(t_ast_simple_command *sc)
{
	t_ast_cmd_suffix	*suffix;
	int					io_number;

	suffix = sc->cmd_suffix;
	io_number = -1;
	while (suffix)
	{
		if (suffix->io_redirect)
		{
			if (suffix->io_redirect->io_number[0])
			{
				if (ft_isstrdigit(suffix->io_redirect->io_number))
					io_number = ft_atoi(suffix->io_redirect->io_number);
				else
					return (-1);
			}
			if (suffix->io_redirect->io_file)
			{
				if (suffix->io_redirect->io_file->op->c == '>'
					|| suffix->io_redirect->io_file->op->e == CLOBBER)
				{
					if (filename_redirect(suffix, io_number, '>'
								, O_CREAT|O_WRONLY) == -1)
						return (-1);
				}
				else if (suffix->io_redirect->io_file->op->e == DGREAT)
				{
					if (filename_redirect(suffix, io_number, '>'
					, O_CREAT|O_WRONLY|O_APPEND) == -1)
						return (-1);
				}
				else if (suffix->io_redirect->io_file->op->c == '<')
				{
					if (filename_redirect(suffix, io_number, '<'
								, O_RDONLY) == -1)
						return (-1);
				}
				else if (suffix->io_redirect->io_file->op->e == GREATAND)
				{
					if (fd_redirect(suffix, io_number, '>') == -1)
						return (-1);
				}
				else if (suffix->io_redirect->io_file->op->e == LESSAND)
				{
					if (fd_redirect(suffix, io_number, '<') == -1)
						return (-1);
				}
			}
			else if (suffix->io_redirect->io_here)
			{
				if (suffix->io_redirect->io_here->op == DLESS)
				{
					if (here_redirect(suffix, io_number) == -1)
						return (-1);
				}
			}
		}
		suffix = suffix->cmd_suffix;
	}
	return (0);
}
