/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbero <rbarbero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/18 14:50:03 by rbarbero          #+#    #+#             */
/*   Updated: 2018/11/04 16:45:24 by rbarbero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"
#include "libft.h"
#include "eval.h"

static int	simple_redirs(t_ast_io_redirect *io_redirect, int io_number
		, t_list **redirs)
{
	int	status;

	status = 0;
	if (io_redirect->io_file->op == GREAT
		|| io_redirect->io_file->op == CLOBBER)
		status = filename_redirect_output(io_redirect, io_number
					, O_CREAT | O_WRONLY | O_TRUNC, redirs);
	else if (io_redirect->io_file->op == DGREAT)
		status = filename_redirect_output(io_redirect, io_number
		, O_CREAT | O_WRONLY | O_APPEND, redirs);
	else if (io_redirect->io_file->op == LESS)
		status = filename_redirect_input(io_redirect, io_number
					, O_RDONLY, redirs);
	else if (io_redirect->io_file->op == GREATAND)
		status = fd_redirect(io_redirect, io_number, '>', redirs);
	else if (io_redirect->io_file->op == LESSAND)
		status = fd_redirect(io_redirect, io_number, '<', redirs);
	return (status);
}

/*
** Select and execute the good redirection depends on the redirection operator.
*/

static int	select_redirs(t_ast_io_redirect *io_redirect, t_list **redirs)
{
	int	status;
	int	io_number;

	io_number = -1;
	status = 0;
	if (io_redirect->io_number[0])
	{
		if (ft_isstrdigit(io_redirect->io_number))
			io_number = ft_atoi(io_redirect->io_number);
		else
			return (-1);
	}
	if (io_redirect->io_file)
		status = simple_redirs(io_redirect, io_number, redirs);
	else if (io_redirect->io_here && io_redirect->io_here->op == DLESS)
		status = here_redirect(io_redirect, io_number, redirs);
	return (status);
}

/*
** Scan a simple_command and get input and output redirections if they exist.
*/

int			do_eval_redirs(t_ast_simple_command *sc, t_list **redirs)
{
	t_ast_cmd_prefix	*prefix;
	t_ast_cmd_suffix	*suffix;

	prefix = sc->cmd_prefix;
	suffix = sc->cmd_suffix;
	while (prefix)
	{
		if (prefix->io_redirect
				&& select_redirs(prefix->io_redirect, redirs) == -1)
			return (-1);
		prefix = prefix->cmd_prefix;
	}
	while (suffix)
	{
		if (suffix->io_redirect
				&& select_redirs(suffix->io_redirect, redirs) == -1)
			return (-1);
		suffix = suffix->cmd_suffix;
	}
	return (0);
}
