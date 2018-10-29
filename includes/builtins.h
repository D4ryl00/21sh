/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbero <rbarbero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/17 16:44:21 by rbarbero          #+#    #+#             */
/*   Updated: 2018/10/29 13:26:57 by rbarbero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

int		builtin_echo(char **av);
int		builtin_env(char **av);
int		builtin_setenv(t_list **env, char **av);
int		builtin_unsetenv(t_list **env, char **av);
void	builtin_exit(char **av);

#endif
