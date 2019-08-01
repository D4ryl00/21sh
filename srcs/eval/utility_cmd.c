/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbero <rbarbero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/05 13:29:58 by rbarbero          #+#    #+#             */
/*   Updated: 2019/08/01 11:26:58 by rbarbero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "sh.h"
#include "eval.h"
#include "utilities.h"

char	*g_utility_cmd[] =
{
	"alias",
	"cd",
	"fg",
	""
};

int		is_utility_cmd(char **av)
{
	if (ft_strarrchr(av[0], g_utility_cmd) >= 0)
		return (1);
	return (0);
}

int		run_utility_cmd(char **av)
{
	(void)av;
	if (!ft_strcmp(av[0], "cd"))
		return (utility_cd(av));
	else if (!ft_strcmp(av[0], "fg"))
		return (utility_fg(av));
	return (0);
}
