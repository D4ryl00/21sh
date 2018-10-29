/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbero <rbarbero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/05 13:26:50 by rbarbero          #+#    #+#             */
/*   Updated: 2018/10/29 12:49:17 by rbarbero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "sh.h"
#include "eval.h"
#include "builtins.h"

char	*g_builtin_cmd[] =
{
	"env",
	"setenv",
	"unsetenv",
	"exit",
	""
};

int		is_builtin_cmd(char **av)
{
	if (ft_strarrchr(av[0], g_builtin_cmd) >= 0)
		return (1);
	return (0);
}

int		run_builtin_cmd(char **av)
{
	if (!ft_strcmp(av[0], "env"))
		builtin_env(av);
	else if (!ft_strcmp(av[0], "setenv"))
		builtin_setenv(&g_env, av);
	else if (!ft_strcmp(av[0], "unsetenv"))
		builtin_unsetenv(&g_env, av);
	else if (!ft_strcmp(av[0], "exit"))
		builtin_exit(av);
	return (0);
}
