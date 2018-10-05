/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbero <rbarbero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/05 09:52:24 by rbarbero          #+#    #+#             */
/*   Updated: 2018/10/05 09:53:04 by rbarbero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "sh.h"

static int	eval_simple_command(t_ast_simple_command *sc, t_pipe_env *pipe_env)
{
	int		status;
	char	**av;

	status = 0;
	av = ast_construct_cmd_args(sc);
	pipe_env->sc = sc;
	status = cmd_search_and_run(av, pipe_env);
	ft_strarrdel(av);
	return (status);
}

int			eval_command(t_ast_command *command, t_pipe_env *pipe_env)
{
	return (eval_simple_command(command->simple_command, pipe_env));
}
