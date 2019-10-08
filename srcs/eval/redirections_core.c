/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_core.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbero <rbarbero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/05 14:06:22 by rbarbero          #+#    #+#             */
/*   Updated: 2019/10/08 11:50:22 by rbarbero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "sh.h"
#include "eval.h"
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

/*
** Redirection [n]< into a file,
** where [n] is an optional fd (default 0).
*/

int			filename_redirect_input(t_ast_io_redirect *io_redirect
		, int io_number, int mode, t_list **redirs)
{
	int			fd;
	t_redirs	save;
	t_list		*node;

	io_number = io_number == -1 ? 0 : io_number;
	t_redirs_init(&save);
	if ((fd = open(io_redirect->io_file->filename->word
		, mode, 0644)) == -1)
		return (return_perror(EOPEN, NULL, -1));
	if (t_redirs_save_fd(&save, io_number) == -1)
		return (-1);
	if (dup2(fd, io_number) == -1)
	{
		close(fd);
		return (return_perror(EDUP, NULL, -1));
	}
	close(fd);
	if (!(node = ft_lstnew(&save, sizeof(t_redirs))))
		exit_perror(ENOMEM, NULL);
	ft_lstadd(redirs, node);
	return (0);
}

/*
** Redirection [n]> or [n]>> or [n]>| into a file,
** where [n] is an optional fd (default 1).
*/

int			filename_redirect_output(t_ast_io_redirect *io_redirect
		, int io_number, int mode, t_list **redirs)
{
	int			fd;
	t_redirs	save;
	t_list		*node;

	io_number = io_number == -1 ? 1 : io_number;
	t_redirs_init(&save);
	if ((fd = open(io_redirect->io_file->filename->word
		, mode, 0644)) == -1)
		return (return_perror(EOPEN, NULL, -1));
	if (t_redirs_save_fd(&save, io_number) == -1)
		return (-1);
	if (dup2(fd, io_number) == -1)
	{
		close(fd);
		return (return_perror(EDUP, NULL, -1));
	}
	close(fd);
	if (!(node = ft_lstnew(&save, sizeof(t_redirs))))
		exit_perror(ENOMEM, NULL);
	ft_lstadd(redirs, node);
	return (0);
}

/*
** Redirections [n]>&- or [n]<&- to close a fd,
** or to a file ([n]>&file)
*/

static int	fd_redirect_other(t_ast_io_redirect *io_redirect, int io_number
		, char op, t_list **redirs)
{
	t_redirs	save;
	t_list		*node;

	t_redirs_init(&save);
	if (!ft_strcmp(io_redirect->io_file->filename->word, "-"))
	{
		if (t_redirs_save_fd(&save, io_number) == -1)
			return (-1);
		close(io_number);
		if (!(node = ft_lstnew(&save, sizeof(t_redirs))))
			exit_perror(ENOMEM, NULL);
		ft_lstadd(redirs, node);
	}
	else if (op == '>')
		return (filename_redirect_output(io_redirect, io_number
					, O_CREAT | O_WRONLY, redirs));
	else
	{
		return (filename_redirect_input(io_redirect, io_number
					, O_CREAT | O_RDONLY, redirs));
	}
	return (0);
}

/*
** Redirection [n]>& or [n]<& into an other fd,
** where [n] is an optional fd (default 1 for >& and 0 for <&)
*/

int			fd_redirect(t_ast_io_redirect *io_redirect, int io_number, char op
		, t_list **redirs)
{
	t_redirs	save;
	t_list		*node;

	if (io_number == -1)
		io_number = op == '>' ? 1 : 0;
	t_redirs_init(&save);
	if (ft_isstrdigit(io_redirect->io_file->filename->word))
	{
		if (t_redirs_save_fd(&save, io_number) == -1)
			return (-1);
		if (dup2(ft_atoi(io_redirect->io_file->filename->word)
		, io_number) == -1)
			return (return_perror(EDUP, NULL, -1));
		if (!(node = ft_lstnew(&save, sizeof(t_redirs))))
			exit_perror(ENOMEM, NULL);
		ft_lstadd(redirs, node);
	}
	else
		return (fd_redirect_other(io_redirect, io_number, op, redirs));
	return (0);
}
