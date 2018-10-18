/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eval.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbero <rbarbero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/18 11:45:30 by rbarbero          #+#    #+#             */
/*   Updated: 2018/10/18 18:38:04 by rbarbero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"
#include "libft.h"
#include "lexer.h"
#include "parser.h"
#include "eval.h"
#include <stdlib.h>

/*
** Print a new prompt de get new tokens.
** Connect the old token list with the new for no leaks
*/

int			get_new_tokens(t_list **empty_tokens, t_list *start)
{
	t_input	input;

	input.save = NULL;
	input.str = NULL;
	if (*empty_tokens)
		ft_lstdel(empty_tokens, token_free);
	newprompt(&input, "> ");
	if (!(*empty_tokens = lexer(&input)))
	{
		free(input.save);
		return (-1);
	}
	if (start)
	{
		while ((start)->next)
			start = start->next;
		start->next = *empty_tokens;
	}
	else
		start = *empty_tokens;
	return (0);
}

/*static void	print_tokens(t_list *tokens)
{
	enum e_token	type;

	while (tokens)
	{
		type = ((t_token *)tokens->content)->type;
		ft_printf("%s(%d)", ((t_token *)tokens->content)->content
				, ((t_token *)tokens->content)->type);
		if (tokens->next)
			ft_putstr(" | ");
		tokens = tokens->next;
	}
	ft_putchar('\n');
}*/

int			eval(t_input *input)
{
	t_list			*tokens;
	t_ast_program	*program;

	if (!(tokens = lexer(input)))
	{
		free(input->save);
		input->save = NULL;
		input->str = NULL;
		return (-1);
	}
	free(input->save);
	input->save = NULL;
	input->str = NULL;
	program = NULL;
	//print_tokens(tokens);
	if (ast_program(&program, tokens) > 0)
		eval_program(program);
	ft_lstdel(&tokens, token_free);
	free_ast_program(program);
	return (0);
}
