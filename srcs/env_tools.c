/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_tools.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbero <rbarbero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/16 23:18:00 by rbarbero          #+#    #+#             */
/*   Updated: 2018/09/16 23:29:32 by rbarbero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"
#include "libft.h"

/*
** return the address of the '=' character in a string
*/
char	*p_to_equ_char(char *str)
{
	while (*str)
	{
		if (*str == '=')
			return (str);
		str++;
	}
	return (NULL);
}

/*
** node is a list of strings formated by key=value.
** Return 1 (true) if the key of the string is equal to data
** else return 0 (false)
*/
int		env_select_key(t_list *node, void *data)
{
	size_t	len;
	char	*pequ;

	if (!(pequ = p_to_equ_char(node->content)))
		return (0);
	len = pequ - (char *)node->content;
	return (ft_strnequ(node->content, data, len));
}
