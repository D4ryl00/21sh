/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_core_other.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbero <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/15 14:44:45 by rbarbero          #+#    #+#             */
/*   Updated: 2019/10/15 14:46:44 by rbarbero         ###   ########.fr       */
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
	if (word_expansion(&l_name, str, QUOTE_REMOVAL) == -1)
		return (NULL);
	filename = ft_strdup(l_name->content);
	ft_lstdel(&l_name, word_expansion_del_node);
	return (filename);
}
