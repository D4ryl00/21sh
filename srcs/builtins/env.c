/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbero <rbarbero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/17 18:56:09 by rbarbero          #+#    #+#             */
/*   Updated: 2019/07/31 16:17:52 by rbarbero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"
#include "libft.h"
#include "builtins.h"
#include "eval.h"

static int	eval_option(t_list **env, char **av, int *i)
{
	int	status;

	status = 0;
	if (av[*i] && av[*i][0] == '-')
	{
		if (!ft_strcmp(av[(*i)++], "-i"))
			ft_lstdel(env, env_del_entry);
		else
		{
			ft_putendl("Usage: env [-i] [name=value]... "
					"[utility [argument...]]");
			status = 1;
		}
	}
	return (status);
}

static void	print_env(t_list *env)
{
	while (env)
	{
		ft_putendl(env->content);
		env = env->next;
	}
}

static void	eval_setenv(t_list **env, char **av, int *i)
{
	char	*args[4];
	char	*pos;

	args[0] = "env";
	args[1] = NULL;
	args[2] = NULL;
	args[3] = NULL;
	while (av[*i] && ft_strchr(av[*i], '='))
	{
		pos = p_to_equ_char(av[*i]);
		if (!(args[1] = ft_strndup(av[*i], pos - av[*i]))
				|| !(args[2] = ft_strdup(pos + 1)))
			exit_perror(ENOMEM, NULL);
		builtin_setenv(env, args);
		free(args[1]);
		free(args[2]);
		(*i)++;
	}
}

static int	launch_utility(char **av, int *i, t_list *env)
{
	char	**export_env;
	int		status;

	status = 0;
	if (av[*i])
	{
		if (!(export_env = ft_lsttoarrstr(env)))
			exit_perror(ENOMEM, NULL);
		status = cmd_select_type(&(av[*i]), export_env);
		ft_strarrdel(export_env);
	}
	else
		print_env(env);
	return (status);
}

int			builtin_env(char **av)
{
	t_list	*env;
	int		status;
	int		i;

	i = 1;
	status = 0;
	if (!(env = ft_lstdup(g_env)))
		exit_perror(ENOMEM, NULL);
	status = eval_option(&env, av, &i);
	if (!status)
	{
		eval_setenv(&env, av, &i);
		status = launch_utility(av, &i, env);
	}
	ft_lstdel(&env, env_del_entry);
	return (status);
}
