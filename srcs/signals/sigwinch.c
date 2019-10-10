/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sigwinch.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amordret <amordret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/01 13:31:00 by amordret          #+#    #+#             */
/*   Updated: 2019/10/10 14:53:53 by amordret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void    sig_winch(int a)
{
    //struct sigaction	action;
	//int					status;

    if (a == -1 || g_s == NULL)
    	return ;
	//action.sa_handler = SIG_IGN;
	//status = sigaction(SIGWINCH, &action, NULL);
    g_s->c[0] = 0;
	//reprint_after(g_s);
    //action.sa_handler = &sig_winch;
	//status = sigaction(SIGWINCH, &action, NULL);
}