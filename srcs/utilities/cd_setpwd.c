/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_setpwd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbero <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 15:55:25 by rbarbero          #+#    #+#             */
/*   Updated: 2019/10/09 15:58:50 by rbarbero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"
#include "libft.h"

static t_list	*new_env_node(t_list **env)
{
	t_list	*entry;

	if (!(entry = (t_list *)malloc(sizeof(t_list))))
	{
		ft_perror(ENOMEM, NULL, 0);
		return (NULL);
	}
	entry->content = NULL;
	entry->content_size = 0;
	entry->next = NULL;
	ft_lstaddback(env, entry);
	return (entry);
}

void			set_oldpwd(t_list **env)
{
	t_list	*entry;
	char	*pwd;
	char	*value;

	if (!(pwd = env_get_value("PWD")))
		pwd = "";
	if (!(entry = ft_lstselect(*env, "OLDPWD", env_select_key)))
	{
		if (!(entry = new_env_node(env)))
			return ;
	}
	else
		free(entry->content);
	if (ft_sprintf(&value, "%s=%s", "OLDPWD", pwd) == -1)
	{
		free(pwd);
		ft_perror(ENOMEM, NULL, 0);
		return ;
	}
	entry->content = (void *)value;
	entry->content_size = ft_strlen(value) + 1;
}

void			set_pwd(t_list **env, const char *path)
{
	t_list	*entry;
	char	*value;

	if (!(entry = ft_lstselect(*env, "PWD", env_select_key)))
	{
		if (!(entry = new_env_node(env)))
			return ;
	}
	else
		free(entry->content);
	if (ft_sprintf(&value, "%s=%s", "PWD", path) == -1)
	{
		ft_perror(ENOMEM, NULL, 0);
		return ;
	}
	entry->content = (void *)value;
	entry->content_size = ft_strlen(value) + 1;
}
