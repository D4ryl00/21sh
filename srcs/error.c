/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amordret <amordret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/30 22:09:25 by rbarbero          #+#    #+#             */
/*   Updated: 2018/09/15 20:18:59 by rbarbero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"
#include "libft.h"
#include <stdlib.h>

char			*g_errors[] =
{
	"Not enough space/cannot allocate memory",
	"command not found",
	"No such file or directory",
	"Permission denied",
	"Buffer error, irrecoverable, exiting...",
	"Fork error",
	""
};

void	exit_perror(enum e_errno num, char *str)
{
	if (str)
		ft_dprintf(2, "42sh: %s: %s\n", str, g_errors[num]);
	else
		ft_dprintf(2, "42sh: %s\n", g_errors[num]);
	termcaps_reset_term_and_exit();
}

int		return_perror(enum e_errno num, char *str)
{
	if (str)
		ft_dprintf(2, "42: %s: %s\n", str, g_errors[num]);
	else
		ft_dprintf(2, "42: %s\n", g_errors[num]);
	return (-1);
}
