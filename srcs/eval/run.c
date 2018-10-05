/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amordret <amordret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/15 17:48:21 by rbarbero          #+#    #+#             */
/*   Updated: 2018/10/05 15:04:36 by rbarbero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"
#include "libft.h"
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

/*
**	Get fd of an opened pipe and dup them on stdin or stdout.
*/

static int	run_eval_pipe(t_pipe_env *pipe_env)
{
	if ((pipe_env->input.rd != -1)
			&& (dup2(pipe_env->input.rd, pipe_env->input.wr) == -1))
		return (return_perror(EDUP, NULL));
	if ((pipe_env->output.rd != -1)
			&& (dup2(pipe_env->output.wr, pipe_env->output.rd) == -1))
		return (return_perror(EDUP, NULL));
	return (0);
}

/*
** Execute the command in a fork and execve.
** Perform redirections and pipe if needed.
*/

int			run(char *path, char **av, t_pipe_env *pipe_env)
{
	pid_t	pid;
	int		status;
	char	**env;
	int		ret;

	if (!(pid = fork()))
	{
		if (!(env = ft_lsttoarrstr(g_env)))
			exit_perror(ENOMEM, NULL);
		if ((run_eval_pipe(pipe_env) == -1)
				|| (run_eval_redirs(pipe_env->sc) == -1))
			return (-1);
		termcaps_reset_term();
		execve(path, av, env);
		return (0);
	}
	else if (pid == -1)
		return (return_perror(EFORK, NULL));
	ret = wait(&status);
	ft_set_term();
	if (ret == -1)
		return (return_perror(EWAIT, NULL));
	return (WEXITSTATUS(status));
}
