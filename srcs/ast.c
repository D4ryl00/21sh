/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbero <rbarbero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/12 16:05:04 by rbarbero          #+#    #+#             */
/*   Updated: 2018/09/12 17:20:35 by rbarbero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "sh.h"
#include <stdlib.h>

t_ast_simple_command	*create_simple_command(t_btree *ast, t_list *tokens)
{
	t_ast_simple_command	*sc;

	if (!(sc = (t_ast_simple_command *)malloc(sizeof(t_ast_simple_command))))
		exit_perror(ENOMEM, NULL);
	if (sc->cmd_name = create_cmd_name(ast, tokens))
		sc->cmd_suffix = create_cmd_suffix(ast, tokens);
}

t_ast_command			*create_command(t_btree *ast, t_list *tokens)
{
	t_command	*command;

	if (!(command = (t_ast_command *)malloc(sizeof(t_ast_command))))
		exit_perror(ENOMEM, NULL);
	return (command);
}

t_ast_program	create_program(t_list *tokens)
{
	t_ast_program	*program;

	if (!(program = (t_ast_program *)malloc(sizeof(t_ast_program))))
		exit_perror(ENOMEM, NULL);
	if (create_command(ast, tokens))
		tokens = tokens->next;
	return (0);
}

t_ast_program	*make_ast(t_list *tokens)
{
	t_ast_program	*program;

	if (!(program = create_program(tokens)))
		ft_printf("21sh: parse error near `%s\n'", tokens->content);
	return (program);
}
