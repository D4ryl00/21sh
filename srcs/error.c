/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amordret <amordret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/30 22:09:25 by rbarbero          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2018/09/13 16:34:39 by amordret         ###   ########.fr       */
=======
/*   Updated: 2018/09/13 16:31:55 by rbarbero         ###   ########.fr       */
>>>>>>> 0ca6c5e150ffa28279d9aab8d78588ae73e46ca4
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
