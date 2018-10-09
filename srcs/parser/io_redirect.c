/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io_redirect.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbero <rbarbero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/05 07:50:39 by rbarbero          #+#    #+#             */
/*   Updated: 2018/10/09 06:24:33 by rbarbero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "sh.h"
#include "parser.h"

/*
** Init a ast_io_redirect with default values
*/

static void	ast_io_redirect_init(t_ast_io_redirect *redirect)
{
	if (redirect)
	{
		redirect->io_number[0] = '\0';
		redirect->io_file = NULL;
		redirect->io_here = NULL;
	}
}

/*
** Free a whole ast_io_redirect structure and set the pointer NULL.
*/

static int	ast_io_redirect_error(t_ast_io_redirect **redirect, int status)
{
	if (redirect && *redirect)
	{
		free_ast_io_redirect(*redirect);
		*redirect = NULL;
	}
	return (status);
}

/*
** make io_redirect structure (see shell grammar)
*/

int			ast_io_redirect(t_ast_io_redirect **redirect, t_list **tokens)
{
	int	status;

	if (*tokens)
	{
		if (!(*redirect = (t_ast_io_redirect *)malloc(
						sizeof(t_ast_io_redirect))))
			exit_perror(ENOMEM, NULL);
		ast_io_redirect_init(*redirect);
		if (((t_token *)(*tokens)->content)->type == IO_NUMBER)
		{
			ft_strncpy((*redirect)->io_number, ((t_token *)(*tokens)->content)
					->content, IO_NUMBER_SIZE);
			(*redirect)->io_number[3] = '\0';
			*tokens = (*tokens)->next;
		}
		if ((status = ast_io_file(&((*redirect)->io_file), tokens)) < 1
				&& (status == -1
				|| (status = ast_io_here(&((*redirect)->io_here), tokens)) < 1))
			return (ast_io_redirect_error(redirect, status));
		return (1);
	}
	return (0);
}

void		free_ast_io_redirect(t_ast_io_redirect *redirect)
{
	if (redirect)
	{
		if (redirect->io_file)
			free_ast_io_file(redirect->io_file);
		if (redirect->io_here)
			free_ast_io_here(redirect->io_here);
		free(redirect);
	}
}
