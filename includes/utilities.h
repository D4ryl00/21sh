/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbero <rbarbero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/09 07:14:18 by rbarbero          #+#    #+#             */
/*   Updated: 2019/10/09 17:04:39 by rbarbero         ###   ########.fr       */
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

/*
** cd
*/

int				utility_cd(char **av);
void			cd_init_params(t_cd_params *params);
void			cd_get_params(t_cd_params *params, char **av);
int				cd_hyphen(void);
int				cd_add_pwd(char **path);
void			set_oldpwd(t_list **env);
void			set_pwd(t_list **env, const char *path);
int				cd_path_to_canonical(char *path);
int				cd_is_dot_dot_component(char *path, int i);
int				cd_dot_dot_process(char *path, int i);
char			*cd_select_cdpath(t_cd_params *params);

/*
** fg, bg
*/

int				utility_fg(char **av);
int				utility_bg(char **av);
int				job_get_arg(char **av);
struct s_job	*job_find(t_list *jobs, unsigned int job_id);

int				utility_jobs(char **av);

#endif
