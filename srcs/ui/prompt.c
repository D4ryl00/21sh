/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amordret <amordret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/09 13:48:23 by amordret          #+#    #+#             */
/*   Updated: 2018/11/07 11:03:01 by amordret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

static void	sh_print_prompt(void)
{
	char	*pwd;
	
	pwd = NULL;
	if (!(((pwd = getenv("PWD")) == NULL)))
	{
		term_putstr_fd(PROMPT1, 2);
		term_putstr_fd(pwd, 2);
		g_termcaps.promptlength = ft_strlen(pwd);
	}
	term_putstr_fd(PROMPT2, 2);
	term_putstr_fd(PROMPT3, 2);
	g_termcaps.promptlength += 4;
	g_termcaps.writtenchars = 0;
}

void		prompt(char *promptstring)
{
	g_termcaps.promptlength = 0;
	if (promptstring)
	{
		term_putstr_fd(promptstring, 2);
		g_termcaps.promptlength = ft_strlen(promptstring);
		g_termcaps.writtenchars = 0;
	}
	else
		sh_print_prompt();
}
