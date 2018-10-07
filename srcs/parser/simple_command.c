/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbero <rbarbero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/05 07:56:09 by rbarbero          #+#    #+#             */
/*   Updated: 2018/10/07 12:15:27 by rbarbero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "sh.h"
#include "parser.h"

int		ast_simple_command(t_ast_simple_command **sc, t_list **tokens)
{
	int	status;

	if (*tokens)
	{
		if (!(*sc = (t_ast_simple_command *)malloc(sizeof
						(t_ast_simple_command))))
			exit_perror(ENOMEM, NULL);
		(*sc)->cmd_prefix = NULL;
		(*sc)->cmd_word = NULL;
		(*sc)->cmd_name = NULL;
		(*sc)->cmd_suffix = NULL;
		if ((status = ast_cmd_prefix(&((*sc)->cmd_prefix), tokens)) > 0)
		{
			if ((status = ast_cmd_word(&((*sc)->cmd_word), tokens)) > 0)
			{
				if ((status = ast_cmd_suffix(&((*sc)->cmd_suffix), tokens)) == -1)
				{
					free_ast_simple_command(*sc);
					*sc = NULL;
					return (status);
				}
			}
			else if (status == -1)
			{
				free_ast_simple_command(*sc);
				*sc = NULL;
				return (status);
			}
		}
		else if (!status && (status = ast_cmd_name(&((*sc)->cmd_name), tokens)) > 0)
		{
			if ((status = ast_cmd_suffix(&((*sc)->cmd_suffix), tokens)) == -1)
			{
				free_ast_simple_command(*sc);
				*sc = NULL;
				return (status);
			}
		}
		else
		{
			free_ast_simple_command(*sc);
			*sc = NULL;
			return (status);
		}
		return (1);
	}
	return (0);
}

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
