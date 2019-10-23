/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_get_filename.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbero <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/15 14:44:45 by rbarbero          #+#    #+#             */
/*   Updated: 2019/10/23 14:44:24 by rbarbero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "sh.h"
#include "eval.h"

char	*redir_get_filename(const char *str)
{
	char	*filename;
	t_list	*l_name;

	l_name = NULL;
	if (word_expansion(&l_name, str, TILDE | PARAMETER | QUOTE) == -1)
		return (NULL);
	filename = ft_strdup(l_name->content);
	ft_lstdel(&l_name, word_expansion_del_node);
	return (filename);
}
