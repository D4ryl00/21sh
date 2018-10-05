/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amordret <amordret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/09 13:48:23 by amordret          #+#    #+#             */
/*   Updated: 2018/10/05 15:28:34 by amordret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

static void	sh_print_prompt(void)
{
	char	*pwd;
	
	pwd = NULL;
	if (!(((pwd = getenv("PWD")) == NULL)))
	{
		term_putstr(PROMPT1);
		term_putstr(pwd);
		g_termcaps.promptlength = ft_strlen(pwd);
	}
	term_putstr(PROMPT2);
	term_putstr(PROMPT3);
	g_termcaps.promptlength += 4;
	g_termcaps.writtenchars = 0;
}

void		prompt(char *promptstring)
{
	g_termcaps.promptlength = 0;
	if (promptstring)
	{
		term_putstr(promptstring);
		g_termcaps.promptlength = ft_strlen(promptstring);
	}
	else
		sh_print_prompt();
}
