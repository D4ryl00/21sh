/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amordret <amordret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/05 13:26:50 by rbarbero          #+#    #+#             */
/*   Updated: 2018/11/09 14:45:04 by amordret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "sh.h"
#include "eval.h"
#include "builtins.h"

char	*g_builtin_cmd[] =
{
	"echo",
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
	int	status;

	status = 1; //A VERIFIER DANS LA LOGIQUE C'ETAIT POUR QUE CLANG ARRETE DE ME CASSER LES COUILLES
	//DANS LE CAS D'UN RETURN DE STATUS NON-INITIALISE
	//ENCORE COMMENTAIRE POUR FAIRE GUEULER LA NORMINETTE POUR TE FORCER A REGARDER
	/*
	ET ENCORE UN DE PLUS 
	*/
	if (!ft_strcmp(av[0], "echo"))
		status = builtin_echo(av);
	else if (!ft_strcmp(av[0], "env"))
		status = builtin_env(av);
	else if (!ft_strcmp(av[0], "setenv"))
		status = builtin_setenv(&g_env, av);
	else if (!ft_strcmp(av[0], "unsetenv"))
		status = builtin_unsetenv(&g_env, av);
	else if (!ft_strcmp(av[0], "exit"))
		builtin_exit(av);
	return (status);
}
