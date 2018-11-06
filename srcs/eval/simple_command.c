/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbero <rbarbero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/05 11:06:29 by rbarbero          #+#    #+#             */
/*   Updated: 2018/10/29 10:34:04 by rbarbero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "sh.h"
#include "eval.h"

/*
** For a simple_command, return the number of arguments of the command.
*/

static int	ast_get_cmd_args_size(t_ast_simple_command *sc)
{
	int					size;
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
** For a simple_command, return the command name for execve
*/

static char	*ast_get_cmd_name(t_ast_simple_command *sc)
{
	if (sc && sc->cmd_word && sc->cmd_word->word)
		return (sc->cmd_word->word);
	if (sc && sc->cmd_name && sc->cmd_name->word)
		return (sc->cmd_name->word);
	else
		return (NULL);
}

/*
** For a simple_command, return an array of string with arguments
** of the command for execve. It's begin by the command name
** and terminate by a NULL pointer.
*/

static char	**ast_construct_cmd_args(t_ast_simple_command *sc)
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
** Evalutation of an simple_command (shell grammar POSIX)
*/

int			eval_simple_command(t_ast_simple_command *sc, int wait)
{
	int		status;
	char	**av;
	char	**env;
	t_list	*redirs;

	status = 0;
	redirs = NULL;
	if (!(env = ft_lsttoarrstr(g_env)))
		exit_perror(ENOMEM, NULL);
	av = ast_construct_cmd_args(sc);
	if (do_eval_redirs(sc, &redirs) == -1)
		return (-1);
	status = cmd_select_type(av, wait, env);
	if (undo_redirs(&redirs) == -1)
		return (-1);
	ft_strarrdel(av);
	ft_strarrdel(env);
	return (status);
}
