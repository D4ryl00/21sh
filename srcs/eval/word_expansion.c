/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_expansion.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbero <rbarbero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/12 17:57:09 by rbarbero          #+#    #+#             */
/*   Updated: 2019/10/16 23:22:48 by rbarbero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "sh.h"
#include "eval.h"

int		word_expansion(t_list **out, const char *in, int options)
{
	int		status;
	t_list	*node;

	status = 0;
	if (in && options)
	{
		if (!(node = ft_lstpushback(out, (void *)in,
					sizeof(char) * (ft_strlen(in) + 1))))
			return_perror(ENOMEM, NULL, -1);
		if (options & TILDE_EXPANSION)
			status |= tilde_expansion(node);
		if (options & QUOTE_REMOVAL)
			status |= quote_removal(node);
	}
	return (status);
}

void	word_expansion_del_node(void *content, size_t size)
{
	(void)size;
	free(content);
}
