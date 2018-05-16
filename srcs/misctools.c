/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   misctools.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amordret <amordret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/15 18:15:42 by amordret          #+#    #+#             */
/*   Updated: 2018/05/16 12:54:35 by amordret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void	termcaps_echoandputchar(char c)
{
	termcaps_echo(1);
	ft_putchar(c);
	termcaps_echo(0);
}

void	termcaps_echoandputstr(char *s)
{
	termcaps_echo(1);
	ft_putstr(s);
	termcaps_echo(0);
}
