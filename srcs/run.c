/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbero <rbarbero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/15 17:48:21 by rbarbero          #+#    #+#             */
/*   Updated: 2018/09/16 01:42:43 by rbarbero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"
#include "libft.h"

int	exec_builtin(char *name, char **args)
{
	(void)name;
	(void)args;
	return (0);
}

int	exec_special_builtin(char *name, char **args)
{
	(void)name;
	(void)args;
	return (0);
}

int	exec_utility(char *name, char **args)
{
	(void)name;
	(void)args;
	return (0);
}

int	exec_cmd(char *name, char **args)
{
	(void)name;
	(void)args;
	return (0);
}

int	cmd_search(char *name, char **args)
{
	if (!ft_strchr(name, '/'))
	{
		if (!exec_builtin(name, args))
			;
		else if (!exec_special_builtin(name, args))
			;
		else if (!exec_utility(name, args))
			;
		else
			exec_cmd(name, args);
	}
	/*if (!access(name, F_OK))
	{
		if (!access(name, X_OK))
		{
			execve(name, args, NULL);
			ft_strarrdel(args);
			args = NULL;
		}
		else
			return_perror(EACCES, name);
	}
	else
		return_perror(ENOCMD, name);*/
	return (0);
}
