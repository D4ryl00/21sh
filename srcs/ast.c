/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbero <rbarbero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/12 16:05:04 by rbarbero          #+#    #+#             */
/*   Updated: 2018/09/13 16:37:51 by rbarbero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "sh.h"
#include <stdlib.h>

t_ast_cmd_name			*ast_cmd_name(t_list *tokens)
{
	t_ast_cmd_name	*name;

	name = NULL;
	if (tokens)
	{
		if (!(name = (t_ast_cmd_name *)malloc(sizeof(t_ast_cmd_name))))
			exit_perror(ENOMEM, NULL);
		if (!(name->word = ft_strdup(tokens->content)))
			exit_perror(ENOMEM, NULL);
	}
	return (name);
}

t_ast_cmd_suffix		*ast_cmd_suffix(t_list *tokens)
{
	t_ast_cmd_suffix	*suffix;

	suffix = NULL;
	if (tokens)
	{
		if (!(suffix = (t_ast_cmd_suffix *)malloc(sizeof(t_ast_cmd_suffix))))
			exit_perror(ENOMEM, NULL);
		//while (
	}
	return (suffix);
}

t_ast_simple_command	*ast_simple_command(t_list *tokens)
{
	t_ast_simple_command	*sc;
	t_ast_cmd_suffix		*suffix;

	sc = NULL;
	if (tokens)
	{
		if (!(sc = (t_ast_simple_command *)malloc(sizeof(t_ast_simple_command))))
			exit_perror(ENOMEM, NULL);
		if ((sc->cmd_name = ast_cmd_name(tokens)))
			suffix = ast_cmd_suffix(tokens);
		else
			free_ast_simple_command(sc);
	}
	return (sc);
}

t_ast_command			*ast_command(t_list *tokens)
{
	t_ast_command	*command;

	command = NULL;
	if (tokens)
	{
		if (!(command = (t_ast_command *)malloc(sizeof(t_ast_command))))
			exit_perror(ENOMEM, NULL);
		if (!(command->simple_command = ast_simple_command(tokens)))
		{
			free_ast_command(command);
			command = NULL;
		}
	}
	return (command);
}

t_ast_program	*ast_program(t_list *tokens)
{
	t_ast_program	*program;

	program = NULL;
	if (tokens)
	{
		if (!(program = (t_ast_program *)malloc(sizeof(t_ast_program))))
			exit_perror(ENOMEM, NULL);
		// ici tester les différentes solutions, et si aucune, alors free
		if (!(program->command = ast_command(tokens)))
		{
			free_ast_program(program);
			program = NULL;
		}
	}
	return (program);
}

t_ast_program	*make_ast(t_list *tokens)
{
	t_ast_program	*program;

	program = NULL;
	if (tokens)
	{
		if (!(program = ast_program(tokens)))
			ft_printf("21sh: parse error near `%s\n'", tokens->content);
	}
	return (program);
}
