/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbero <rbarbero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/29 12:40:46 by rbarbero          #+#    #+#             */
/*   Updated: 2018/10/29 12:55:28 by rbarbero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"
#include "builtins.h"

void	builtin_exit(char **av)
{
	if (av[1] && !ft_isstrdigit(av[1]))
	{
		ft_perror(ENONUM, av[1], 0);
		termcaps_reset_term_and_exit(255);
	}
	termcaps_reset_term_and_exit(av[1] ? ft_atoi(av[1]) : 0);
}
