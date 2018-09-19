/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_cmd_tools.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbero <rbarbero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/18 14:50:03 by rbarbero          #+#    #+#             */
/*   Updated: 2018/09/19 19:07:28 by rbarbero         ###   ########.fr       */
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
** Scan a simple_command and get input and output redirections if they exist.
** Set the address of the structures in the args.
*/

int	cmd_ast_eval_redirs(t_ast_simple_command *sc)
{
	t_ast_cmd_suffix	*suffix;
	t_ast_io_file		*file;
	t_ast_io_here		*here;
	int					fd;
	int					io_number;

	suffix = sc->cmd_suffix;
	while (suffix)
	{
		if (suffix->io_redirect)
		{
			if ((file = suffix->io_redirect->io_file))
			{
				if (file->op->c == '>')
				{
					if ((fd = open(file->filename->word, O_CREAT|O_WRONLY, 0644)) == -1)
						ft_perror(EOPEN, NULL);
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
				}
			}
			else if ((here = suffix->io_redirect->io_here))
			{
			}
		}
		suffix = suffix->cmd_suffix;
	}
	return (0);
}

void	cmd_ast_undo_redirs(t_list *backup)
{
	t_io_redir_done	*rdone;

	while (backup)
	{
		rdone = backup->content;
		if (dup2(rdone->dup.target, rdone->dup.source) == -1)
			ft_perror(EDUP, NULL);
		close(rdone->open);
		backup = backup->next;
	}
}
