/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbero <rbarbero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/09 07:14:18 by rbarbero          #+#    #+#             */
/*   Updated: 2018/10/09 08:35:27 by rbarbero         ###   ########.fr       */
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
#endif
