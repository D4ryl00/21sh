/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_cmd_tools.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbero <rbarbero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/18 14:50:03 by rbarbero          #+#    #+#             */
/*   Updated: 2018/09/21 23:43:16 by rbarbero         ###   ########.fr       */
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

static int	filename_redirect(t_ast_cmd_suffix *suffix, char op, int mode)
{
	int	fd;
	int	io_number;

	if ((fd = open(suffix->io_redirect->io_file->filename->word
		, mode, 0644)) == -1)
		return (return_perror(EOPEN, NULL));
	else
	{
		if (suffix->io_redirect->io_number[0])
			io_number = ft_atoi(suffix->io_redirect->io_number);
		else
			io_number = op == '>' ? 1 : 0;
		if (dup2(fd, io_number) == -1)
		{
			close(fd);
			return (return_perror(EDUP, NULL));
		}
		close(fd);
	}
	return (0);
}

/*
** Redirection [n]>& or [n]<& into an other fd,
** where [n] is an optional fd (default 1 for >& and 0 for <&)
*/

static int	fd_redirect(t_ast_cmd_suffix *suffix, char op)
{
	int	io_number;

	if (ft_isstrdigit(suffix->io_redirect->io_file->filename->word))
	{
		if (suffix->io_redirect->io_number[0])
			io_number = ft_atoi(suffix->io_redirect->io_number);
		else
			io_number = op == '>' ? 1 : 0;
		if (dup2(ft_atoi(suffix->io_redirect->io_file->filename->word)
		, io_number) == -1)
			return (return_perror(EDUP, NULL));
	}
	else if (op == '>')
		return (filename_redirect(suffix, '>', O_CREAT|O_WRONLY));
	else
		return (filename_redirect(suffix, '<', O_CREAT|O_RDONLY));
	return (0);
}

/*
** For here documents, call the newprompt function until catch the keyword
*/

int	here_redirect(t_ast_cmd_suffix *suffix)
{
	char	*key;
	t_input	*input;
	int		status;
	t_buf	here;

	input = NULL;
	if (ft_buf_init(&here) == -1)
		exit_perror(ENOMEM, NULL);
	key = suffix->io_redirect->io_file->filename->word;
	while ((status = newprompt(input, "> ") != -1)
			&& ft_strcmp(input->str, key))
	{
	}
	if (status == -1)
		exit_perror(ENOMEM, NULL);
	//ft_buf_destroy(&buffer);
	return (0);
}

/*
** Scan a simple_command and get input and output redirections if they exist.
** Set the address of the structures in the args.
*/

int	cmd_ast_eval_redirs(t_ast_simple_command *sc)
{
	t_ast_cmd_suffix	*suffix;

	suffix = sc->cmd_suffix;
	while (suffix)
	{
		if (suffix->io_redirect)
		{
			if (suffix->io_redirect->io_file)
			{
				if (suffix->io_redirect->io_file->op->c == '>'
					|| suffix->io_redirect->io_file->op->e == CLOBBER)
				{
					if (filename_redirect(suffix, '>', O_CREAT|O_WRONLY) == -1)
						return (-1);
				}
				else if (suffix->io_redirect->io_file->op->e == DGREAT)
				{
					if (filename_redirect(suffix, '>'
					, O_CREAT|O_WRONLY|O_APPEND) == -1)
						return (-1);
				}
				else if (suffix->io_redirect->io_file->op->c == '<')
				{
					if (filename_redirect(suffix, '<', O_RDONLY) == -1)
						return (-1);
				}
				else if (suffix->io_redirect->io_file->op->e == GREATAND)
				{
					if (fd_redirect(suffix, '>') == -1)
						return (-1);
				}
				else if (suffix->io_redirect->io_file->op->e == LESSAND)
				{
					if (fd_redirect(suffix, '<') == -1)
						return (-1);
				}
				else if (suffix->io_redirect->io_file->op->e == DLESS)
				{
					if (here_redirect(suffix) == -1)
						return (-1);
				}
			}
			else if (suffix->io_redirect->io_here)
			{
			}
		}
		suffix = suffix->cmd_suffix;
	}
	return (0);
}
