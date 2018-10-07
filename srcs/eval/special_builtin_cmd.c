/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   special_builtin_cmd.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbero <rbarbero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/05 13:28:35 by rbarbero          #+#    #+#             */
/*   Updated: 2018/10/07 12:17:49 by rbarbero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "sh.h"
#include "eval.h"

char	*g_special_builtin_cmd[] =
{
	"alloc",
	""
};

int		is_special_builtin_cmd(char **av)
{
	if (ft_strarrchr(av[0], g_special_builtin_cmd) >= 0)
		return (1);
	return (0);
}

int		run_special_builtin_cmd(char **av)
{
	(void)av;
	return (0);
}
