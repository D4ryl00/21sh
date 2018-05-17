/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eval.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amordret <amordret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/18 11:45:30 by rbarbero          #+#    #+#             */
/*   Updated: 2018/05/17 14:40:40 by rbarbero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"
#include "libft.h"
#include <stdlib.h>

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

t_btree	*eval(t_btree *ast, t_input *input)
{
	t_list			*tokens;
	enum e_token	type;

	if (!(tokens = get_tokens(input)))
	{
		//free(input);
		return (NULL);
	}
	//free(input);
	while (tokens)
	{
		type = ((t_token *)tokens->content)->type;
		ft_printf("%s(%s)", ((t_token *)tokens->content)->content, type == WORD ? "WORD" : "OPERATOR");
		if (tokens->next)
			ft_putstr(" | ");
		ft_lstdelnode(&tokens, tokens, token_free);
	}
	ft_putchar('\n');
	//ast = parse_tokens(tokens);
	return (ast);
}
