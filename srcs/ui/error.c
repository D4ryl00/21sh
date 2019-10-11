/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amordret <amordret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/30 22:09:25 by rbarbero          #+#    #+#             */
/*   Updated: 2019/10/11 14:28:29 by amordret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"
#include "libft.h"
#include <stdlib.h>

char			*g_errors[] =
{
	"Not enough space/cannot allocate memory",
	"Command not found",
	"No such file or directory",
	"Not a directory",
	"Permission denied",
	"Buffer error, irrecoverable, exiting...",
	"syntax error near unexpected token",
	"Fork error",
	"Wait error",
	"Open error",
	"Dup error",
	"Pipe error",
	"numeric argument required",
	""
};

void	exit_perror(enum e_errno num, char *str)
{
	if (str)
		ft_dprintf(2, "42sh: %s: %s\n", str, g_errors[num]);
	else
		ft_dprintf(2, "42sh: %s\n", g_errors[num]);
	if (num != EOTHER)
		termcaps_reset_term_and_exit(1);
	exit(1);
}

int		return_perror(enum e_errno num, char *str, int value)
{
	if (str)
		ft_dprintf(2, "42sh: %s: %s\n", str, g_errors[num]);
	else
		ft_dprintf(2, "42sh: %s\n", g_errors[num]);
	return (value);
}

int		return_print(char *str, int status)
{
	if (str)
	{
		ft_dprintf(2, str);
	}
	return (status);
}

/*
** Print an error of g_error selected by e_errno.
** suffix tell if str is print before or after the previous error.
*/

void	ft_perror(enum e_errno num, char *str, int suffix)
{
	if (str && suffix)
		ft_dprintf(2, "42sh: %s: %s\n", g_errors[num], str);
	else if (str)
		ft_dprintf(2, "42sh: %s: %s\n", str, g_errors[num]);
	else
		ft_dprintf(2, "42sh: %s\n", g_errors[num]);
}
