/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filename.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbero <rbarbero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/05 07:41:08 by rbarbero          #+#    #+#             */
/*   Updated: 2018/10/07 12:14:05 by rbarbero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "sh.h"
#include "parser.h"

int		ast_filename(t_ast_filename **filename, t_list **tokens)
{
	if (*tokens && ((t_token *)(*tokens)->content)->type == TOKEN)
	{
		if (!(*filename = (t_ast_filename *)malloc(sizeof(t_ast_filename))))
			exit_perror(ENOMEM, NULL);
		if (!((*filename)->word = ft_strdup(((t_token *)(*tokens)->content)
						->content)))
			exit_perror(ENOMEM, NULL);
		*tokens = (*tokens)->next;
		return (1);
	}
	ft_perror(ESYNT, *tokens ? ((t_token *)(*tokens)->content)->content : "NULL"
			, 1);
	return (-1);
}

void	free_ast_filename(t_ast_filename *filename)
{
	if (filename)
	{
		if (filename->word)
			free(filename->word);
		free(filename);
	}
}
