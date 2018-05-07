/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   int_mod_flags.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbero <rbarbero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/15 16:47:47 by rbarbero          #+#    #+#             */
/*   Updated: 2018/04/01 23:43:36 by rbarbero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_vsdprintf.h"
#include "libft.h"
#include <locale.h>
#include <stdlib.h>

char	*int_mod_space(char **str)
{
	char	*res;

	if ((*str)[0] != '-')
	{
		if (!(res = ft_strjoin(" ", *str)))
			return (NULL);
		free(*str);
		*str = res;
	}
	return (*str);
}

char	*int_mod_plus(char **str)
{
	char	*res;

	if ((*str)[0] != '-')
	{
		if (!(res = ft_strjoin("+", *str)))
			return (NULL);
		free(*str);
		*str = res;
	}
	return (*str);
}

char	*int_mod_quote(char **str)
{
	char			*res;
	struct lconv	*lconv;
	size_t			str_len;
	int				res_len;
	int				i;

	setlocale(LC_NUMERIC, "");
	lconv = localeconv();
	if (ft_strlen(*str) > 3 && lconv->thousands_sep && lconv->thousands_sep[0])
	{
		str_len = ft_strlen(*str);
		res_len = str_len + (str_len - (**str == '-'
				|| **str == '+' ? 1 : 0) - 1) / 3;
		if (!(res = (char *)ft_memalloc(sizeof(char) * (res_len + 1))))
			return (NULL);
		i = 0;
		while (--res_len >= 0)
			if (i++ && !(i % 4) && res_len)
				res[res_len] = lconv->thousands_sep[0];
			else
				res[res_len] = (*str)[--str_len];
		free(*str);
		*str = res;
	}
	return (*str);
}
