/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io_file.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbero <rbarbero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/05 07:43:38 by rbarbero          #+#    #+#             */
/*   Updated: 2018/10/08 16:51:27 by rbarbero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "sh.h"
#include "parser.h"

/*
** Free a t_ast_io_file structure.
*/

void	free_ast_io_file(t_ast_io_file *file)
{
	if (file)
	{
		if (file->filename)
			free_ast_filename(file->filename);
		if (file->op)
			free(file->op);
		free(file);
	}
}

static int	ast_io_file_eval(t_ast_io_file **file, t_list **tokens)
{
	t_token	*token;
	int		status;

	status = 0;
	token = (t_token *)(*tokens)->content;
	if ((token->type == LESSAND) || (token->type == GREATAND)
			|| (token->type == DGREAT) || (token->type == LESSGREAT)
			|| (token->type == CLOBBER))
	{
		(*file)->op->c = '\0';
		(*file)->op->e = token->type;
		*tokens = (*tokens)->next;
		status = ast_filename(&((*file)->filename), tokens);
	}
	else if (!ft_strcmp(token->content, "<")
			|| !ft_strcmp(token->content, ">"))
	{
		(*file)->op->c = token->content[0];
		*tokens = (*tokens)->next;
		status = ast_filename(&((*file)->filename), tokens);
	}
	return (status);
}

int			ast_io_file(t_ast_io_file **file, t_list **tokens)
{
	int		status;

	status = 0;
	if (*tokens)
	{
		if (!(*file = (t_ast_io_file *)malloc(sizeof(t_ast_io_file)))
				|| !((*file)->op = (t_ast_io_op *)malloc(sizeof(t_ast_io_op))))
			exit_perror(ENOMEM, NULL);
		(*file)->filename = NULL;
		status = ast_io_file_eval(file, tokens);
		if (!((*file)->filename))
		{
			free_ast_io_file(*file);
			*file = NULL;
			return (status);
		}
		return (1);
	}
	return (0);
}
