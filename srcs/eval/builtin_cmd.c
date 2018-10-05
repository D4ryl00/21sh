/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbero <rbarbero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/05 13:26:50 by rbarbero          #+#    #+#             */
/*   Updated: 2018/10/05 13:28:12 by rbarbero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "sh.h"

char	*g_builtin_cmd[] =
{
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
	if (!ft_strcmp(av[0], "exit"))
		termcaps_reset_term_and_exit();
	return (0);
}
