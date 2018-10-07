/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbero <rbarbero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/18 14:50:03 by rbarbero          #+#    #+#             */
/*   Updated: 2018/10/07 12:17:33 by rbarbero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"
#include "libft.h"
#include "eval.h"

static int	simple_redirs(t_ast_io_redirect *io_redirect, int io_number)
{
	int	status;

	status = 0;
	if (io_redirect->io_file->op->c == '>'
		|| io_redirect->io_file->op->e == CLOBBER)
		status = filename_redirect(io_redirect, io_number, '>'
					, O_CREAT|O_WRONLY);
	else if (io_redirect->io_file->op->e == DGREAT)
		status = filename_redirect(io_redirect, io_number, '>'
		, O_CREAT|O_WRONLY|O_APPEND);
	else if (io_redirect->io_file->op->c == '<')
		status = filename_redirect(io_redirect, io_number, '<'
					, O_RDONLY);
	else if (io_redirect->io_file->op->e == GREATAND)
		status = fd_redirect(io_redirect, io_number, '>');
	else if (io_redirect->io_file->op->e == LESSAND)
		status = fd_redirect(io_redirect, io_number, '<');
	return (status);
}

/*
** Select and execute the good redirection depends on the redirection operator.
*/

static int	select_redirs(t_ast_io_redirect *io_redirect)
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
		status = simple_redirs(io_redirect, io_number);
	else if ((io_redirect->io_here) && (io_redirect->io_here->op == DLESS))
			status = here_redirect(io_redirect, io_number);
	return (status);
}

/*
** Scan a simple_command and get input and output redirections if they exist.
*/

int	run_eval_redirs(t_ast_simple_command *sc)
{
	t_ast_cmd_prefix	*prefix;
	t_ast_cmd_suffix	*suffix;

	prefix = sc->cmd_prefix;
	suffix = sc->cmd_suffix;
	while (prefix)
	{
		if (prefix->io_redirect
				&& select_redirs(prefix->io_redirect) == -1)
			return (-1);
		prefix = prefix->cmd_prefix;
	}
	while (suffix)
	{
		if (suffix->io_redirect
				&& select_redirs(suffix->io_redirect) == -1)
			return (-1);
		suffix = suffix->cmd_suffix;
	}
	return (0);
}
