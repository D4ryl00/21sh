/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_suffix.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbero <rbarbero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/05 07:52:08 by rbarbero          #+#    #+#             */
/*   Updated: 2018/10/08 16:34:58 by rbarbero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "sh.h"
#include "parser.h"

/*
** Free the whole structure
*/

void	free_ast_cmd_suffix(t_ast_cmd_suffix *suffix)
{
	if (suffix)
	{
		if (suffix->io_redirect)
			free_ast_io_redirect(suffix->io_redirect);
		if (suffix->word)
			free(suffix->word);
		if (suffix->cmd_suffix)
			free_ast_cmd_suffix(suffix->cmd_suffix);
		free(suffix);
	}
}

/*
** Free the ast_cmd_suffix and set the pointer NULL.
*/

static int	ast_cmd_suffix_error(t_ast_cmd_suffix **suffix, int status)
{
	if (suffix && *suffix)
	{
		free_ast_cmd_suffix(*suffix);
		*suffix = NULL;
	}
	return (status);
}

/*
** Init a cmd_suffix with default values.
*/

static void	ast_cmd_suffix_init(t_ast_cmd_suffix *suffix)
{
	if (suffix)
	{
		suffix->io_redirect = NULL;
		suffix->word = NULL;
		suffix->cmd_suffix = NULL;
	}
}

/*
** construct a suffix of a simple_command (see shell grammar)
*/

int		ast_cmd_suffix(t_ast_cmd_suffix **suffix, t_list **tokens)
{
	if (*tokens)
	{
		if (!(*suffix = (t_ast_cmd_suffix *)malloc(sizeof(t_ast_cmd_suffix))))
			exit_perror(ENOMEM, NULL);
		ast_cmd_suffix_init(*suffix);
		if (ast_io_redirect(&((*suffix)->io_redirect), tokens) == -1)
			return (ast_cmd_suffix_error(suffix, -1));
		if (!((*suffix)->io_redirect)
				&& (((t_token *)(*tokens)->content)->type == TOKEN)
				&& (((t_token *)(*tokens)->content)->type != CONTROL))
		{
			if (!((*suffix)->word = ft_strdup(((t_token *)(*tokens)->content)
							->content)))
				exit_perror(ENOMEM, NULL);
			*tokens = (*tokens)->next;
		}
		if (((*suffix)->io_redirect || (*suffix)->word)
				&& (ast_cmd_suffix(&((*suffix)->cmd_suffix), tokens) == -1))
				return (ast_cmd_suffix_error(suffix, -1));
		if (!(*suffix)->io_redirect && !(*suffix)->word)
			return (ast_cmd_suffix_error(suffix, 0));
		return (1);
	}
	return (0);
}
