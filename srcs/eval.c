/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eval.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbero <rbarbero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/18 11:45:30 by rbarbero          #+#    #+#             */
/*   Updated: 2018/10/03 23:38:26 by rbarbero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"
#include "libft.h"
#include <stdlib.h>

/*
** The order is important. It's linked with e_token.
** PLEASE DO NOT CHANGE THAT!
*/

char			*g_op_token[] =
{
	"&&",
	"||",
	";;",
	"<<",
	">>",
	"<&",
	">&",
	"<>",
	"<<-",
	">|",
	""
};

char			*g_control_operator[] =
{
	"&&",
	"||",
	"|",
	")",
	";",
	"&",
	"!",
	""
};

/*
** Print a new prompt de get new tokens.
** Connect the old token list with the new for no leaks
*/

int	get_new_tokens(t_list **empty_tokens, t_list **start)
{
	t_input	input;

	if (*empty_tokens)
		ft_lstdel(empty_tokens, token_free);
	newprompt(&input, "> ");
	if (!(*empty_tokens = get_tokens(&input)))
	{
		free(input.save);
		return (-1);
	}
	if (*start)
	{
		while ((*start)->next)
			*start = (*start)->next;
		(*start)->next = *empty_tokens;
	}
	else
		*start = *empty_tokens;
	return (0);
}

int	eval(t_input *input)
{
	t_list			*tokens;
	//enum e_token	type;
	t_ast_program	*program;

	if (!(tokens = get_tokens(input)))
	{
		free(input->save);
		return (-1);
	}
	free(input->save);
	input->save = NULL;
	if ((program = make_ast(tokens)))
		eval_program(program);
	ft_lstdel(&tokens, token_free);
	/*while (tokens)
	{
		type = ((t_token *)tokens->content)->type;
		ft_printf("%s(%d)", ((t_token *)tokens->content)->content, ((t_token *)tokens->content)->type);
		if (tokens->next)
			ft_putstr(" | ");
		ft_lstdelnode(&tokens, tokens, token_free);
	}
	ft_putchar('\n');*/
	free_ast_program(program);
	return (0);
}
