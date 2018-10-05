/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_core.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbero <rbarbero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/05 14:06:22 by rbarbero          #+#    #+#             */
/*   Updated: 2018/10/05 15:29:15 by rbarbero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "sh.h"
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

/*
** Redirection [n]> or [n]>> into a file,
** where [n] is an optional fd (default 1).
*/

int			filename_redirect(t_ast_io_redirect *io_redirect, int io_number
		, char op, int mode)
{
	int	fd;

	if (io_number == -1)
		io_number = op == '>' ? 1 : 0;
	if ((fd = open(io_redirect->io_file->filename->word
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

int			fd_redirect(t_ast_io_redirect *io_redirect, int io_number, char op)
{
	if (io_number == -1)
		io_number = op == '>' ? 1 : 0;
	if (ft_isstrdigit(io_redirect->io_file->filename->word))
	{
		if (dup2(ft_atoi(io_redirect->io_file->filename->word)
		, io_number) == -1)
			return (return_perror(EDUP, NULL));
	}
	else if (op == '>')
		return (filename_redirect(io_redirect, io_number, '>'
					, O_CREAT|O_WRONLY));
	else
		return (filename_redirect(io_redirect, io_number, '<'
					, O_CREAT|O_RDONLY));
	return (0);
}

/*
** For here documents, call the newprompt function until catch the keyword
*/

static int	here_loop(t_ast_io_redirect *io_redirect, int fd_pipe[2])
{
	int		status;
	t_input	input;
	int		len;

	status = 0;
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

/*
** Open and close the pipe. Call the here doc loop until read the key.
*/

int			here_redirect(t_ast_io_redirect *io_redirect, int io_number)
{
	int		status;
	int		fd_pipe[2];

	io_number = io_number == -1 ? 0 : io_number;
	if (pipe(fd_pipe) == -1)
		return_perror(EPIPE, NULL);
	if ((fd_pipe[0] == io_number) && ((fd_pipe[0] = dup(fd_pipe[0])) == -1))
		return_perror(EDUP, NULL);
	if ((fd_pipe[1] == io_number) && ((fd_pipe[1] = dup(fd_pipe[1])) == -1))
		return_perror(EDUP, NULL);
	if ((status = here_loop(io_redirect, fd_pipe)) == -1)
		return (-1);
	if (dup2(fd_pipe[0], io_number) == -1)
		return_perror(EDUP, NULL);
	close(fd_pipe[0]);
	close(fd_pipe[1]);
	if (status == -1)
		exit_perror(ENOMEM, NULL);
	return (0);
}
