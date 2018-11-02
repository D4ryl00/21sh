/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io_here.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbero <rbarbero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/05 07:47:05 by rbarbero          #+#    #+#             */
/*   Updated: 2018/11/02 15:20:25 by rbarbero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "sh.h"
#include "parser.h"

static int	eval_io_here(t_ast_io_here **here, t_list **tokens)
{
	if (!((*here)->op = ft_strdup(((t_token *)(*tokens)->content)->
					content)))
		exit_perror(ENOMEM, NULL);
	*tokens = (*tokens)->next;
	return (ast_here_end(&((*here)->here_end), tokens));
}

int		ast_io_here(t_ast_io_here **here, t_list **tokens)
{
	int	status;

	status = 0;
	if (*tokens)
	{
		if (!(*here = (t_ast_io_here *)malloc(sizeof(t_ast_io_here))))
			exit_perror(ENOMEM, NULL);
		(*here)->here_end = NULL;
		(*here)->op = NULL;
		if (!ft_strcmp(((t_token *)(*tokens)->content)->content, "<<")
				|| !ft_strcmp(((t_token *)(*tokens)->content)->content, "<<-"))
			status = eval_io_here(here, tokens);
		if (status < 1)
		{
			free_ast_io_here(*here);
			*here = NULL;
			return (status);
		}
		return (1);
	}
	return (0);
}

void	free_ast_io_here(t_ast_io_here *io_here)
{
	if (io_here)
	{
		if (io_here->here_end)
			free_ast_here_end(io_here->here_end);
		free(io_here);
	}
}
