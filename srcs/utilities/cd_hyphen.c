/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_hyphen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbero <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 15:52:45 by rbarbero          #+#    #+#             */
/*   Updated: 2019/10/09 15:54:01 by rbarbero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"
#include "libft.h"
#include "utilities.h"

int	cd_hyphen(void)
{
	char	*oldpwd;
	char	*av[3];
	int		status;

	status = 0;
	if (!(oldpwd = env_get_value("OLDPWD")) || !oldpwd[0])
		return (return_perror(EOTHER, "cd: OLDPWD not set", 1));
	if (!(oldpwd = ft_strdup(oldpwd)))
		return (return_perror(ENOMEM, NULL, 1));
	av[0] = "cd";
	av[1] = oldpwd;
	av[2] = NULL;
	if (!(status = utility_cd(av)))
		ft_printf("%s\n", oldpwd);
	free(oldpwd);
	return (status);
}
