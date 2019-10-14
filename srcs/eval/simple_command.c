/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbero <rbarbero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/05 11:06:29 by rbarbero          #+#    #+#             */
/*   Updated: 2019/10/14 10:32:20 by rbarbero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "eval.h"
#include "parser.h"
#include "jobcontrol.h"

/*
** For a simple_command, return the number of arguments of the command.
*/

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

static char	**ast_construct_cmd_args(t_ast_simple_command *sc)
{
	t_list				*l_av;
	t_ast_cmd_suffix	*suffix;
	char				**argv;

	l_av = NULL;
	if (word_expansion(&l_av, ast_get_cmd_name(sc), QUOTE_REMOVAL) == -1)
		return (NULL);
	suffix = sc->cmd_suffix;
	while (suffix)
	{
		if (suffix->word)
		{
			if (word_expansion(&l_av, suffix->word, QUOTE_REMOVAL) == -1)
			{
				ft_lstdel(&l_av, word_expansion_del_node);
				return (NULL);
			}
		}
		suffix = suffix->cmd_suffix;
	}
	if (!(argv = ft_lsttoarrstr(l_av)))
		ft_perror(ENOMEM, NULL, 0);
	ft_lstdel(&l_av, word_expansion_del_node);
	return (argv);
}

/*
** For a simple_command, return an array of string with arguments
** of the command for execve. It begins by the command name
** and terminates by a NULL pointer.
*/

void		get_simple_command_cmd_name(t_ast_simple_command *sc,
		t_buf *sc_cmd_name)
{
	char				*str;
	t_ast_cmd_suffix	*suffix;

	if (!(str = ast_get_cmd_name(sc)))
		return ;
	ft_buf_add_str(sc_cmd_name, str);
	suffix = sc->cmd_suffix;
	while (suffix)
	{
		ft_buf_add_char(sc_cmd_name, ' ');
		if (suffix->word)
		{
			if (!(str = ft_strdup(suffix->word)))
				exit_perror(ENOMEM, NULL);
			ft_buf_add_str(sc_cmd_name, str);
			free(str);
		}
		suffix = suffix->cmd_suffix;
	}
}

/*
** Evalutation of an simple_command (shell grammar POSIX)
*/

int			eval_simple_command(t_ast_simple_command *sc)
{
	int			status;
	char		**av;
	char		**env;
	t_list		*redirs;

	status = 0;
	redirs = NULL;
	if (!(env = ft_lsttoarrstr(g_env)))
		exit_perror(ENOMEM, NULL);
	av = ast_construct_cmd_args(sc);
	if (do_eval_redirs(sc, &redirs) == -1)
		return (-1);
	status = cmd_select_type(av, env);
	if (undo_redirs(&redirs) == -1)
		return (-1);
	ft_strarrdel(av);
	ft_strarrdel(env);
	return (status);
}
