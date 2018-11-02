/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredocs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbero <rbarbero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/02 10:33:46 by rbarbero          #+#    #+#             */
/*   Updated: 2018/11/02 10:34:39 by rbarbero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "sh.h"
#include "eval.h"

/*
** For here documents, call the newprompt function until catch the keyword
*/

static int	here_loop(t_ast_io_redirect *io_redirect, int fd_pipe[2])
{
	int		status;
	t_input	input;
	int		len;

	status = 0;
	input.save = NULL;
	while ((status = newprompt(&input, "> ") != -1)
			&& (((len = ft_strlen(input.str)) == 1) || ft_strncmp(input.str
				, io_redirect->io_here->here_end->word, len - 1)))
	{
		write(fd_pipe[1], input.str, len);
		free(input.save);
		input.save = NULL;
		input.str = NULL;
	}
	if (input.save)
		free(input.save);
	return (status);
}

static int	check_fd_pipe(int *fd_pipe, int io_number)
{
	int	tmp;

	if (fd_pipe[0] == io_number)
	{
		if ((tmp = dup(fd_pipe[0])) == -1)
			return_perror(EPIPE, NULL);
		close(fd_pipe[0]);
		fd_pipe[0] = tmp;
	}
	if (fd_pipe[1] == io_number)
	{
		if ((tmp = dup(fd_pipe[1])) == -1)
			return_perror(EPIPE, NULL);
		close(fd_pipe[1]);
		fd_pipe[1] = tmp;
	}
	return (0);
}

/*
** Open and close the pipe. Call the here doc loop until read the key.
*/

int			here_redirect(t_ast_io_redirect *io_redirect, int io_number
		, t_list **redirs)
{
	int			status;
	int			fd_pipe[2];
	t_redirs	save;
	t_list		*node;

	io_number = io_number == -1 ? 0 : io_number;
	t_redirs_init(&save);
	if (t_redirs_save_fd(&save, io_number) == -1)
		return (-1);
	if (pipe(fd_pipe) == -1)
		return_perror(EPIPE, NULL);
	if (check_fd_pipe(fd_pipe, io_number) == -1)
		return (-1);
	if ((status = here_loop(io_redirect, fd_pipe)) == -1)
		return (-1);
	if (dup2(fd_pipe[0], io_number) == -1)
		return_perror(EDUP, NULL);
	if (!(node = ft_lstnew(&save, sizeof(t_redirs))))
		exit_perror(ENOMEM, NULL);
	ft_lstadd(redirs, node);
	close(fd_pipe[0]);
	close(fd_pipe[1]);
	if (status == -1)
		exit_perror(ENOMEM, NULL);
	return (0);
}
