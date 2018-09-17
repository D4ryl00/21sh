/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amordret <amordret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/09 13:48:23 by amordret          #+#    #+#             */
/*   Updated: 2018/09/17 16:44:56 by amordret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

static void	sh_print_prompt(void)
{
	char	*pwd;

	if (!(((pwd = getenv("PWD")) == NULL)))
	{
		ft_putstr(PROMPT1);
		ft_putstr(pwd);
	}
	ft_putstr(PROMPT2);
	ft_putstr(PROMPT3);
	g_termcaps.writtenchars = 0;
}

void		prompt(char *promptstring)
{
	if (promptstring)
		ft_putstr(promptstring);
	else
		sh_print_prompt();
}
