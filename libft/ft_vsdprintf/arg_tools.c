/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_tools.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbero <rbarbero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/21 15:35:59 by rbarbero          #+#    #+#             */
/*   Updated: 2018/04/01 23:39:21 by rbarbero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_vsdprintf.h"
#include "libft.h"
#include <stdlib.h>

static int	t_arg_cmp(t_list *n1, t_list *n2)
{
	if (!n1 && !n2)
		return (0);
	if (!n1)
		return (-1);
	if (!n2)
		return (1);
	return (((t_arg *)n1->content)->pos - ((t_arg *)n2->content)->pos);
}

UCHAR		new_arg(t_list **args, int pos, const char *type, void **data)
{
	t_list	*tmp;
	t_arg	arg;

	arg.pos = pos;
	ft_bzero(arg.type, 4);
	ft_strcpy(arg.type, type);
	arg.data = data;
	if (args)
	{
		if (!(tmp = ft_lstnew(&arg, sizeof(t_arg))))
			return (0);
		ft_lstsortedinsert(args, tmp, t_arg_cmp);
	}
	return (1);
}

char		get_specifier(const char *str)
{
	while (!ft_strchr(CONV_SPEC, *str))
		str++;
	return (*str);
}

void		get_modifier(char *modifier, const char *str)
{
	while (*str && ft_strchr(CONV_MOD, *str))
		*modifier++ = *str++;
	*modifier = '\0';
}

void		take_args(t_list **args, va_list va_args)
{
	char	specifier;

	while (*args)
	{
		specifier = get_specifier(((t_arg *)(*args)->content)->type);
		if (ft_strchr("diouxXpb", specifier))
			take_int_args(*args, va_args);
		else if (specifier == 'c')
			take_char_args(*args, va_args);
		else if (specifier == 's')
			take_str_args(*args, va_args);
		else if (specifier == 'n')
			take_n_args(*args, va_args);
		ft_lstdelnode(args, *args, arg_del);
	}
}
