/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unsetenv.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbero <rbarbero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/17 16:49:35 by rbarbero          #+#    #+#             */
/*   Updated: 2018/10/18 15:27:29 by rbarbero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"
#include "libft.h"
#include "builtins.h"

int	builtin_unsetenv(char **av, t_list *env)
{
	if (av[1])
		ft_lstdelif(&env, av[1], env_select_key, env_del_entry);
	return (0);
}
