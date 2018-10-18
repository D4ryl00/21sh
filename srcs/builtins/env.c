/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbero <rbarbero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/17 18:56:09 by rbarbero          #+#    #+#             */
/*   Updated: 2018/10/18 18:30:59 by rbarbero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"
#include "libft.h"
#include "builtins.h"

static void	print_env(t_list *env)
{
	while (env)
	{
		ft_putendl(env->content);
		env = env->next;
	}
}

int			builtin_env(char **av)
{
	t_list	*env;

	if (!(env = ft_lstdup(g_env)))
		exit_perror(ENOMEM, NULL);
	if (av[1])
	{
		if (av[1][0] == '-')
		{
			if (!ft_strcmp(av[1], "-i"))
				ft_lstdel(&env, env_del_entry);
			else
				ft_putendl("Usage: env [-i] [name=value]... "
						"[utility [argument...]]");
		}
	}
	else
		print_env(env);
	return (0);
}
