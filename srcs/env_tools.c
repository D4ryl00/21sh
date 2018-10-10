/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_tools.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbero <rbarbero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/16 23:18:00 by rbarbero          #+#    #+#             */
/*   Updated: 2018/10/09 09:20:23 by rbarbero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"
#include "libft.h"

/*
** Return key value of g_env if exist.
*/

char	*get_env_value(char *str)
{
	char	*value;
	t_list	*result;
	char	*start_value;

	value = NULL;
	if (str)
	{
		if ((result = ft_lstselect(g_env, str, env_select_key)))
		{
			if ((start_value = p_to_equ_char(result->content)))
				value = start_value + 1;
		}
	}
	return (value);
}

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
