/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setenv.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbero <rbarbero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/17 16:47:56 by rbarbero          #+#    #+#             */
/*   Updated: 2018/10/18 18:06:56 by rbarbero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"
#include "libft.h"
#include "builtins.h"

int	builtin_setenv(char **av, t_list *env)
{
	t_list	*entry;
	char	*value;

	value = NULL;
	if (av[1])
	{
		if (!is_valid_posix_name(av[1]))
			return (return_print("Variable name is not valid\n", 1));
		if (ft_sprintf(&value, "%s=%s", av[1], av[2] ? av[2] : "") == -1)
			exit_perror(ENOMEM, NULL);
		if (!(entry = ft_lstselect(env, av[1], env_select_key)))
		{
			if (!(entry = (t_list *)malloc(sizeof(t_list))))
				exit_perror(ENOMEM, NULL);
			ft_lstaddback(&env, entry);
		}
		else
			free(entry->content);
		entry->content = value;
		entry->content_size = ft_strlen(value);
		entry->next = NULL;
	}
	else
		return (builtin_env(av));
	return (0);
}
