/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbero <rbarbero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/09 07:14:18 by rbarbero          #+#    #+#             */
/*   Updated: 2019/09/20 09:01:38 by rbarbero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILITES_H
# define UTILITES_H

/*
** STRUCTURES
*/

typedef struct	s_cd_params
{
	unsigned char	L;
	unsigned char	P;
	char			*dir;
}				t_cd_params;

/*
** PROTOTYPES
*/

int	utility_cd(char **av);
int	utility_fg(char **av);
int	utility_bg(char **av);
int	utility_jobs(char **av);

#endif
