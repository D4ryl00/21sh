/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eval.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amordret <amordret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/18 11:45:30 by rbarbero          #+#    #+#             */
/*   Updated: 2018/09/15 23:30:24 by rbarbero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"
#include "libft.h"
#include <stdlib.h>

/*
** The order is important. It's linked with e_token.
** PLEASE DO NOT CHANGE THAT!
*/
char			*g_op_token [] =
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

t_ast_program*eval(t_input *input)
{
	t_list			*tokens;
	//enum e_token	type;
	t_ast_program	*program;

	if (!(tokens = get_tokens(input)))
	{
		//free(input);
		return (NULL);
	}
	if (classify_token(tokens) == -1)
		return (NULL);
	//free(input);
	program = make_ast(tokens);
	run_program(program);
/*	while (tokens)
	{
		type = ((t_token *)tokens->content)->type;
		ft_printf("%s(%d)", ((t_token *)tokens->content)->content, ((t_token *)tokens->content)->type);
		if (tokens->next)
			ft_putstr(" | ");
		ft_lstdelnode(&tokens, tokens, token_free);
	}
	ft_putchar('\n');*/
	return (program);
}
