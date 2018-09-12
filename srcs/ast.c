/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbero <rbarbero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/12 16:05:04 by rbarbero          #+#    #+#             */
/*   Updated: 2018/09/13 00:14:28 by rbarbero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "sh.h"
#include <stdlib.h>

t_ast_simple_command	*create_simple_command(t_list *tokens)
{
	t_ast_simple_command	*sc;

	(void)tokens;
	if (!(sc = (t_ast_simple_command *)malloc(sizeof(t_ast_simple_command))))
		exit_perror(ENOMEM, NULL);
	/*if (sc->cmd_name = create_cmd_name(ast, tokens))
		sc->cmd_suffix = create_cmd_suffix(ast, tokens);*/
	return (sc);
}

t_ast_command			*create_command(t_list *tokens)
{
	t_ast_command	*command;

	(void)tokens;
	if (!(command = (t_ast_command *)malloc(sizeof(t_ast_command))))
		exit_perror(ENOMEM, NULL);
	return (command);
}

t_ast_program	*create_program(t_list *tokens)
{
	t_ast_program	*program;

	if (!(program = (t_ast_program *)malloc(sizeof(t_ast_program))))
		exit_perror(ENOMEM, NULL);
	// ici tester les différentes solutions, et si aucune, alors free
	if (!(program->command = create_command(tokens)))
		free_ast_program(program);
	return (program);
}

t_ast_program	*make_ast(t_list *tokens)
{
	t_ast_program	*program;

	program = NULL;
	if (tokens)
	{
		if (!(program = create_program(tokens)))
			ft_printf("21sh: parse error near `%s\n'", tokens->content);
	}
	return (program);
}
