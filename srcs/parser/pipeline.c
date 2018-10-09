/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbero <rbarbero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/05 08:07:10 by rbarbero          #+#    #+#             */
/*   Updated: 2018/10/09 06:26:55 by rbarbero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "sh.h"
#include "parser.h"

int		ast_pipeline(t_ast_pipeline **pipeline, t_list **tokens)
{
	int	status;

	if (*tokens)
	{
		if (!(*pipeline = (t_ast_pipeline *)malloc(sizeof(t_ast_pipeline))))
			exit_perror(ENOMEM, NULL);
		(*pipeline)->pipe_sequence = NULL;
		if (!ft_strcmp(((t_token *)(*tokens)->content)->content, "!"))
		{
			(*pipeline)->bang = '!';
			*tokens = (*tokens)->next;
		}
		else
			(*pipeline)->bang = '\0';
		if ((status = ast_pipe_sequence(&((*pipeline)->pipe_sequence), tokens))
				< 1)
		{
			free_ast_pipeline(*pipeline);
			*pipeline = NULL;
			return (status);
		}
		return (1);
	}
	return (0);
}

void	free_ast_pipeline(t_ast_pipeline *pipeline)
{
	if (pipeline)
	{
		if (pipeline->pipe_sequence)
			free_ast_pipe_sequence(pipeline->pipe_sequence);
		free(pipeline);
	}
}
