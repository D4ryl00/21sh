/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_prefix.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbero <rbarbero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/05 07:54:20 by rbarbero          #+#    #+#             */
/*   Updated: 2019/10/15 13:30:58 by rbarbero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "sh.h"
#include "parser.h"

/*
** Is it a assignment word for a function?
*/

static int	is_assignment_word(char *str)
{
	char	*equal;
	char	*name;

	if ((equal = ft_strchr(str, '=')))
	{
		if (*str == '=')
			return (0);
		if (!(name = ft_strndup(str, equal - str)))
			exit_perror(ENOMEM, NULL);
		if (is_valid_posix_name(name))
			return (1);
	}
	return (0);
}

/*
** Free the whole structure
*/

void		free_ast_cmd_prefix(t_ast_cmd_prefix *prefix)
{
	if (prefix)
	{
		if (prefix->io_redirect)
			free_ast_io_redirect(prefix->io_redirect);
		if (prefix->assignment_word)
			free(prefix->assignment_word);
		if (prefix->cmd_prefix)
			free_ast_cmd_prefix(prefix->cmd_prefix);
		free(prefix);
	}
}

/*
** Free the ast_cmd_prefix and set the pointer NULL.
*/

static int	ast_cmd_prefix_error(t_ast_cmd_prefix **prefix, int status)
{
	if (prefix && *prefix)
	{
		free_ast_cmd_prefix(*prefix);
		*prefix = NULL;
	}
	return (status);
}

static void	init_struct(t_ast_cmd_prefix **prefix)
{
	(*prefix)->io_redirect = NULL;
	(*prefix)->assignment_word = NULL;
	(*prefix)->cmd_prefix = NULL;
}

/*
** construct a prefix of a simple_command (see shell grammar)
*/

int			ast_cmd_prefix(t_ast_cmd_prefix **prefix, t_list **tokens)
{
	int	status;

	if (*tokens)
	{
		if (!(*prefix = (t_ast_cmd_prefix *)malloc(sizeof(t_ast_cmd_prefix))))
			exit_perror(ENOMEM, NULL);
		init_struct(prefix);
		if ((status = ast_io_redirect(&((*prefix)->io_redirect), tokens)) < 0)
			return (ast_cmd_prefix_error(prefix, status));
		else if (!((*prefix)->io_redirect) && is_assignment_word(((t_token *)
						(*tokens)->content) ->content))
		{
			if (!((*prefix)->assignment_word = ft_strdup(((t_token *)(*tokens)->
								content)->content)))
				exit_perror(ENOMEM, NULL);
			*tokens = (*tokens)->next;
		}
		if (((*prefix)->io_redirect || (*prefix)->assignment_word) && ((status =
						ast_cmd_prefix(&((*prefix)->cmd_prefix), tokens)) < 0))
			return (ast_cmd_prefix_error(prefix, -1));
		if (!(*prefix)->io_redirect && !(*prefix)->assignment_word)
			return (ast_cmd_prefix_error(prefix, 0));
		return (1);
	}
	return (0);
}
