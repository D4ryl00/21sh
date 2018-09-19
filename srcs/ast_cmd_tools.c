/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_cmd_tools.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbero <rbarbero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/18 14:50:03 by rbarbero          #+#    #+#             */
/*   Updated: 2018/09/19 21:56:56 by rbarbero         ###   ########.fr       */
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

static int output_redirect(t_ast_cmd_suffix *suffix, int mode)
{
	int	fd;
	int	io_number;

	if ((fd = open(suffix->io_redirect->io_file->filename->word, mode, 0644)) == -1)
		return (return_perror(EOPEN, NULL));
	else
	{
		if (suffix->io_redirect->io_number[0])
			io_number = ft_atoi(suffix->io_redirect->io_number);
		else
			io_number = 1;
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
					if (output_redirect(suffix, O_CREAT|O_WRONLY) == -1)
						return (-1);
				}
				else if (suffix->io_redirect->io_file->op->e == DGREAT)
				{
					if (output_redirect(suffix, O_CREAT|O_WRONLY|O_APPEND) == -1)
						return (-1);
				}
				else if (suffix->io_redirect->io_file->op->e == DGREAT)
				{
					if (output_redirect(suffix, O_CREAT|O_WRONLY|O_APPEND) == -1)
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