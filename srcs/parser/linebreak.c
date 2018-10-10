/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linebreak.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbero <rbarbero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/05 08:04:33 by rbarbero          #+#    #+#             */
/*   Updated: 2018/10/07 12:14:29 by rbarbero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "sh.h"
#include "parser.h"

int		ast_linebreak(t_ast_linebreak **linebreak, t_list **tokens)
{
	if (*tokens)
	{
		if (!(*linebreak = (t_ast_linebreak *)malloc(sizeof(t_ast_linebreak))))
			exit_perror(ENOMEM, NULL);
		(*linebreak)->newline_list = NULL;
		if (!ast_newline_list(&((*linebreak)->newline_list), tokens))
		{
			free_ast_linebreak(*linebreak);
			*linebreak = NULL;
		}
	}
	return (1);
}

void	free_ast_linebreak(t_ast_linebreak *linebreak)
{
	if (linebreak)
	{
		if (linebreak->newline_list)
			free_ast_newline_list(linebreak->newline_list);
		free(linebreak);
	}
}
