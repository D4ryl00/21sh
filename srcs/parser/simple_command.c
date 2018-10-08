/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbero <rbarbero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/05 07:56:09 by rbarbero          #+#    #+#             */
/*   Updated: 2018/10/08 17:12:34 by rbarbero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "sh.h"
#include "parser.h"

void	free_ast_simple_command(t_ast_simple_command *sc)
{
	if (sc)
	{
		if (sc->cmd_prefix)
			free_ast_cmd_prefix(sc->cmd_prefix);
		if (sc->cmd_word)
			free_ast_cmd_word(sc->cmd_word);
		if (sc->cmd_name)
			free_ast_cmd_name(sc->cmd_name);
		if (sc->cmd_suffix)
			free_ast_cmd_suffix(sc->cmd_suffix);
		free(sc);
	}
}

static int	ast_simple_command_error(t_ast_simple_command **sc, int status)
{
	if (sc && *sc)
	{
		free_ast_simple_command(*sc);
		*sc = NULL;
	}
	return (status);
}

static void	ast_simple_command_init(t_ast_simple_command *sc)
{
	if (sc)
	{
		sc->cmd_prefix = NULL;
		sc->cmd_word = NULL;
		sc->cmd_name = NULL;
		sc->cmd_suffix = NULL;
	}
}

int			ast_simple_command(t_ast_simple_command **sc, t_list **tokens)
{
	int	status;

	if (*tokens)
	{
		if (!(*sc = (t_ast_simple_command *)malloc(sizeof
						(t_ast_simple_command))))
			exit_perror(ENOMEM, NULL);
		ast_simple_command_init(*sc);
		if ((status = ast_cmd_prefix(&((*sc)->cmd_prefix), tokens)) > 0)
		{
			if ((status = ast_cmd_word(&((*sc)->cmd_word), tokens)) > 0)
				status = ast_cmd_suffix(&((*sc)->cmd_suffix), tokens);
			if (status == -1)
				return (ast_simple_command_error(sc, status));
		}
		else if (!status && (status = ast_cmd_name(&((*sc)->cmd_name), tokens)) > 0)
		{
			if ((status = ast_cmd_suffix(&((*sc)->cmd_suffix), tokens)) == -1)
				return (ast_simple_command_error(sc, status));
		}
		else
			return (ast_simple_command_error(sc, status));
		return (1);
	}
	return (0);
}
