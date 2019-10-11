/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amordret <amordret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/31 18:16:23 by rbarbero          #+#    #+#             */
/*   Updated: 2019/10/11 13:50:25 by amordret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNALS_H
# define SIGNALS_H

# include <signal.h>

# if __APPLE
#  define SA_HANDLER __sigaction_u.__sa_handler
#  define SA_SIGACTION __sigaction_u.__sa_sigaction
# else
#  define SA_HANDLER sa_handler
#  define SA_SIGACTION sa_sigaction
# endif

/*
** PROTOTYPES
*/

int			signals_init(void);
int			signals_restore(void);

#endif
