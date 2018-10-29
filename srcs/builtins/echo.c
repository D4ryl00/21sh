/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbero <rbarbero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/29 13:25:55 by rbarbero          #+#    #+#             */
/*   Updated: 2018/10/29 17:09:29 by rbarbero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "sh.h"

static char	get_special_char(char *p, int *status)
{
	char	c;

	c = 0;
	if (*(p + 1) == 'a')
		c = 0x07;
	else if (*(p + 1) == 'b')
		c = 0x08;
	else if (*(p + 1) == 'c')
		*status = 1;
	else if (*(p + 1) == 'f')
		c = 0x0C;
	else if (*(p + 1) == 'n')
		c = 0x0A;
	else if (*(p + 1) == 'r')
		c = 0x0D;
	else if (*(p + 1) == 't')
		c = 0x09;
	else if (*(p + 1) == 'v')
		c = 0x0B;
	else if (*(p + 1) == '\\')
		c = '\\';
	return (c);
}

static int	print_escape_char(char **p)
{
	int		step;
	int		status;
	char	c;

	status = 0;
	step = 2;
	if (!(c = get_special_char(*p, &status)))
	{
		c = '\\';
		step = 1;
	}
	if (!status)
		write(1, &c, 1);
	*p += step;
	return (status);
}

static int	eval_op(char *op)
{
	char	*p;
	int		status;

	status = 0;
	p = op;
	while (*p)
	{
		while (*p && *p != '\\')
			p++;
		if (p != op)
			write(1, op, p - op);
		if (*p && (status = print_escape_char(&p)))
			break ;
		op = p;
	}
	return (status);
}

int			builtin_echo(char **av)
{
	int	status;

	status = 0;
	while (*(av + 1) && !(status = eval_op(*(av++ + 1))))
		write(1, " ", 1);
	if (!status)
		write(1, "\n", 1);
	return (0);
}
