/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_suffix.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbero <rbarbero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/05 07:52:08 by rbarbero          #+#    #+#             */
/*   Updated: 2018/10/05 07:53:03 by rbarbero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "sh.h"

int		ast_cmd_suffix(t_ast_cmd_suffix **suffix, t_list **tokens)
{
	int	status;

	if (*tokens)
	{
		if (!(*suffix = (struct s_ast_cmd_suffix *)
					malloc(sizeof(struct s_ast_cmd_suffix))))
			exit_perror(ENOMEM, NULL);
		(*suffix)->io_redirect = NULL;
		(*suffix)->word = NULL;
		(*suffix)->cmd_suffix = NULL;
		if (!(status = ast_io_redirect(&((*suffix)->io_redirect), tokens)))
		{
			if ((((t_token *)(*tokens)->content)->type == TOKEN)
					&& (((t_token *)(*tokens)->content)->type != CONTROL))
			{
				if (!((*suffix)->word = ft_strdup(((t_token *)(*tokens)->content)
								->content)))
					exit_perror(ENOMEM, NULL);
				*tokens = (*tokens)->next;
			}
		}
		else if (status == -1)
		{
			free_ast_cmd_suffix(*suffix);
			*suffix = NULL;
			return (-1);
		}
		if ((*suffix)->io_redirect || (*suffix)->word)
		{
			if ((status = ast_cmd_suffix(&((*suffix)->cmd_suffix), tokens)) == -1)
				{
					free_ast_cmd_suffix(*suffix);
					*suffix = NULL;
					return (status);
				}
		}
		if (!(*suffix)->io_redirect && !(*suffix)->word)
		{
			free_ast_cmd_suffix(*suffix);
			*suffix = NULL;
			return (0);
		}
		return (1);
	}
	return (0);
}

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

