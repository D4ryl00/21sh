/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_expansion.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbero <rbarbero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/12 17:57:09 by rbarbero          #+#    #+#             */
/*   Updated: 2019/10/13 03:32:09 by rbarbero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "sh.h"
#include "eval.h"

int	word_expansion(t_list **out, const char *in, int options)
{
	int	status;

	status = 0;
	if (in)
	{
		if (options & QUOTE_REMOVAL)
			status |= quote_removal(out, in);
		else
			status = -1;
	}
	return (status);
}
