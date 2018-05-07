/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplittolst.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbero <rbarbero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/17 11:26:23 by rbarbero          #+#    #+#             */
/*   Updated: 2017/11/17 15:53:39 by rbarbero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** t_list	*ft_strsplittolst(char const *s, char c);
** This function takes a NUL terminating string and split each word separated
** by c character.
** A new list is created and each word is a node of this list, in the same
** that string.
*/

#include <stdlib.h>
#include <string.h>
#include "libft.h"

static t_list	*addnode(t_list **lst, const char *s, size_t size)
{
	t_list	*tmp;
	char	*str;

	if (!(str = malloc(size)))
		return (NULL);
	str = ft_strncpy(str, s, size - 1);
	str[size - 1] = '\0';
	if (!(tmp = ft_lstnewnode(&tmp, str, size)))
		return (NULL);
	if (!*lst)
		*lst = tmp;
	else
		(*lst)->next = tmp;
	free(str);
	return (tmp);
}

static void		free_memory(t_list *lst)
{
	t_list	*next;

	while (lst)
	{
		next = lst->next;
		free(lst->content);
		free(lst);
		lst = next;
	}
}

t_list			*ft_strsplittolst(char const *s, char c)
{
	t_list		*lst;
	t_list		*p;
	const char	*start;
	char		first;

	lst = NULL;
	p = NULL;
	first = 1;
	while (*s)
	{
		while (*s && *s == c)
			s++;
		start = s;
		while (*s && *s != c)
			s++;
		if (s - start > 0 && !(p = addnode(&p, start, s - start + 1)))
		{
			free_memory(lst);
			return (NULL);
		}
		lst = first ? p : lst;
		first = 0;
	}
	return (lst);
}
