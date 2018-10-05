/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_prefix.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbero <rbarbero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/05 07:54:20 by rbarbero          #+#    #+#             */
/*   Updated: 2018/10/05 08:20:03 by rbarbero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "sh.h"

static int	is_valid_name(char *str)
{
	if (!*str || ft_isdigit(*str))
		return (0);
	while (*str)
	{
		if (*str != '_' && !ft_isalnum(*str))
			return (0);
		str++;
	}
	return (1);
}

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
		if (is_valid_name(name))
			return (1);
	}
	return (0);
}

int			ast_cmd_prefix(t_ast_cmd_prefix **prefix, t_list **tokens)
{
	int	status;

	if (*tokens)
	{
		if (!(*prefix = (struct s_ast_cmd_prefix *)
					malloc(sizeof(struct s_ast_cmd_prefix))))
			exit_perror(ENOMEM, NULL);
		(*prefix)->io_redirect = NULL;
		(*prefix)->assignment_word = NULL;
		(*prefix)->cmd_prefix = NULL;
		if (!(status = ast_io_redirect(&((*prefix)->io_redirect), tokens)))
		{
			if (is_assignment_word(((t_token *)(*tokens)->content)->content))
			{
				if (!((*prefix)->assignment_word =
							ft_strdup(((t_token *)(*tokens)->content)
								->content)))
					exit_perror(ENOMEM, NULL);
				*tokens = (*tokens)->next;
			}
		}
		else if (status == -1)
		{
			free_ast_cmd_prefix(*prefix);
			*prefix = NULL;
			return (0);
		}
		if ((*prefix)->io_redirect || (*prefix)->assignment_word)
		{
			if ((status = ast_cmd_prefix(&((*prefix)->cmd_prefix), tokens)) == -1)
			{
				free_ast_cmd_prefix(*prefix);
				*prefix = NULL;
				return (-1);
			}
		}
		if (!(*prefix)->io_redirect && !(*prefix)->assignment_word)
		{
			free_ast_cmd_prefix(*prefix);
			*prefix = NULL;
			return (0);
		}
		return (1);
	}
	return (0);
}

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
