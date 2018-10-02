/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eval.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbero <rbarbero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/18 11:45:30 by rbarbero          #+#    #+#             */
/*   Updated: 2018/10/02 16:40:42 by rbarbero         ###   ########.fr       */
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
	"&"
};

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
