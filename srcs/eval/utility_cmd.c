/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbero <rbarbero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/05 13:29:58 by rbarbero          #+#    #+#             */
/*   Updated: 2018/10/07 12:17:55 by rbarbero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "sh.h"
#include "eval.h"

char	*g_utility_cmd[] =
{
	"alias",
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
	return (0);
}
