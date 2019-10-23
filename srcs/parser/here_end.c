/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_end.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbero <rbarbero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/05 07:45:33 by rbarbero          #+#    #+#             */
/*   Updated: 2019/10/23 14:42:52 by rbarbero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "sh.h"
#include "parser.h"
#include "eval.h"

static char	*get_end_word(const char *str)
{
	char	*word;
	t_list	*l_name;

	l_name = NULL;
	if (!str)
		return (NULL);
	if (word_expansion(&l_name, str, QUOTE) == -1)
		return (NULL);
	word = ft_strdup(l_name->content);
	ft_lstdel(&l_name, word_expansion_del_node);
	return (word);
}

int			ast_here_end(t_ast_here_end **here_end, t_list **tokens)
{
	if (*tokens && ((t_token *)(*tokens)->content)->type == TOKEN)
	{
		if (!(*here_end = (t_ast_here_end *)malloc(sizeof(t_ast_here_end))))
			exit_perror(ENOMEM, NULL);
		if (!((*here_end)->word = get_end_word(((t_token *)(*tokens)->content)
						->content)))
			return (-1);
		*tokens = (*tokens)->next;
		return (1);
	}
	return (-1);
}

void		free_ast_here_end(t_ast_here_end *here_end)
{
	if (here_end)
	{
		if (here_end->word)
			free(here_end->word);
		free(here_end);
	}
}
