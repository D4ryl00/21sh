/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tilde_expansion.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbero <rbarbero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/16 22:36:30 by rbarbero          #+#    #+#             */
/*   Updated: 2019/10/16 23:54:04 by rbarbero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "sh.h"
#include "eval.h"

/*
** sizeof(res): sizeof(char) * (strlen(home) + strlen(input) - 1 + 1)
** -1 because we remplace '~' by HOME
** +1 for ending \0
*/

int	tilde_expansion(t_list *node)
{
	char		*res;
	size_t		res_size;
	const char	*input = (const char *)node->content;
	const char	*home = env_get_value("HOME");

	if (!home)
		return_perror(EOTHER, "tilde expansion: HOME is not set", -1);
	if (input[0] == '~' && (input[1] == '/' || !input[1]))
	{
		res_size = sizeof(char) * (ft_strlen(home) + ft_strlen(input));
		if (!(res = (char *)malloc(res_size)))
		{
			free((void *)home);
			return_perror(ENOMEM, NULL, -1);
		}
		ft_strcpy(res, home);
		ft_strcat(res, &input[1]);
		free(node->content);
		node->content = res;
		node->content_size = res_size;
	}
	return (0);
}
