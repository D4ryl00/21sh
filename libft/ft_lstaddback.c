/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstaddback.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbero <rbarbero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/23 06:39:10 by rbarbero          #+#    #+#             */
/*   Updated: 2018/03/23 06:46:50 by rbarbero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstaddback(t_list **alst, t_list *new)
{
	t_list	*p;

	if (!*alst)
		*alst = new;
	else
	{
		p = *alst;
		while (p->next)
			p = p->next;
		p->next = new;
	}
}
