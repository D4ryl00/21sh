/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eval.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amordret <amordret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/18 11:45:30 by rbarbero          #+#    #+#             */
/*   Updated: 2019/10/11 16:20:13 by rbarbero         ###   ########.fr       */
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
	if (newprompt(&input, "> ") == -1)
		return (0);
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

int			eval(t_input *input)
{
	t_list			*tokens;
	t_ast_program	*program;

	program = NULL;
	tokens = lexer(input);
	free(input->save);
	input->save = NULL;
	input->str = NULL;
	if (!tokens)
		return (-1);
	if (ast_program(&program, tokens) > 0)
	{
		termcaps_reset_term();
		eval_program(program);
	}
	do_job_notification();
	ft_lstdel(&tokens, token_free);
	free_ast_program(program);
	return (0);
}
