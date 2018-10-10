/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   program.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbero <rbarbero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/05 08:12:56 by rbarbero          #+#    #+#             */
/*   Updated: 2018/10/09 06:27:54 by rbarbero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "sh.h"
#include "parser.h"

int		ast_program(t_ast_program **program, t_list *tokens)
{
	int	status;

	if (tokens)
	{
		if (!(*program = (t_ast_program *)malloc(sizeof(t_ast_program))))
			exit_perror(ENOMEM, NULL);
		(*program)->linebreak = NULL;
		(*program)->complete_commands = NULL;
		(*program)->post_linebreak = NULL;
		ast_linebreak(&((*program)->linebreak), &tokens);
		if ((status = ast_complete_commands(&((*program)->complete_commands)
						, &tokens)) > 0)
			ast_linebreak(&((*program)->post_linebreak), &tokens);
		if (!(*program)->linebreak && status < 1)
		{
			free_ast_program(*program);
			*program = NULL;
			return (status);
		}
		return (1);
	}
	return (0);
}

void	free_ast_program(t_ast_program *program)
{
	if (program)
	{
		if (program->linebreak)
			free_ast_linebreak(program->linebreak);
		if (program->complete_commands)
			free_ast_complete_commands(program->complete_commands);
		if (program->post_linebreak)
			free_ast_linebreak(program->post_linebreak);
		free(program);
	}
}
