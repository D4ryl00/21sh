/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbero <rbarbero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/09 07:14:18 by rbarbero          #+#    #+#             */
/*   Updated: 2019/08/01 11:19:19 by rbarbero         ###   ########.fr       */
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

#endif
