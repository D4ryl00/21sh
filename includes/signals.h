/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbero <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/31 18:16:23 by rbarbero          #+#    #+#             */
/*   Updated: 2019/08/02 09:11:49 by rbarbero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef SIGNALS_H
# define SIGNALS_H

# include <signal.h>

# if __APPLE
# define sa_handler __sigaction_u.__sa_handler
# define sa_sigaction __sigaction_u.__sa_sigaction
#endif

/*
** PROTOTYPES
*/

int			signals_init(void);
int			signals_restore(void);

#endif
