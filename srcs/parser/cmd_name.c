/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_name.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbero <rbarbero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/05 06:06:52 by rbarbero          #+#    #+#             */
/*   Updated: 2018/10/05 07:58:54 by rbarbero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "sh.h"

int		ast_cmd_name(t_ast_cmd_name **name, t_list **tokens)
{
	if (*tokens && ((t_token *)(*tokens)->content)->type == TOKEN)
	{
		if (!(*name = (t_ast_cmd_name *)malloc(sizeof(t_ast_cmd_name))))
			exit_perror(ENOMEM, NULL);
		if (!((*name)->word = ft_strdup(((t_token *)(*tokens)->content)->content)))
			exit_perror(ENOMEM, NULL);
		*tokens = (*tokens)->next;
		return (1);
	}
	ft_perror(ESYNT, ((t_token *)(*tokens)->content)->content, 1);
	return (-1);
}

void	free_ast_cmd_name(t_ast_cmd_name *cmd_name)
{
	if (cmd_name)
	{
		if (cmd_name->word)
			free(cmd_name->word);
		free(cmd_name);
	}
}
