/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbero <rbarbero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/17 18:56:09 by rbarbero          #+#    #+#             */
/*   Updated: 2018/10/18 19:22:39 by rbarbero         ###   ########.fr       */
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

static void	eval_setenv(char **av, int i, t_list *env)
{
	char	*args[3];
	char	*pos;

	args[0] = NULL;
	args[1] = NULL;
	args[2] = NULL;
	while (av[i] && ft_strchr(av[i], '='))
	{
		pos = p_to_equ_char(av[i]);
		if (!(args[0] = ft_strndup(av[i], pos - av[i]))
				|| !(args[1] = ft_strdup(pos + 1)))
			exit_perror(ENOMEM, NULL);
		builtin_setenv(args, env);
		free(args[0]);
		free(args[1]);
	}
	//if (av[i])
	//	cmd_select_type
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
		else if (av[2])
			eval_setenv(av, 2, env);
	}
	else
		print_env(env);
	return (0);
}
