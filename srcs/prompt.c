/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amordret <amordret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/09 13:48:23 by amordret          #+#    #+#             */
/*   Updated: 2018/09/25 11:53:43 by amordret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

static void	sh_print_prompt(void)
{
	char	*pwd;
	
	pwd = NULL;
	/*if (!(((pwd = getenv("PWD")) == NULL)))
	{
		term_putstr(PROMPT1);
		term_putstr(pwd);
	}
	term_putstr(PROMPT2);
	term_putstr(PROMPT3);*/
	term_putstr("> ");
	g_termcaps.writtenchars = 0;
}

void		prompt(char *promptstring)
{
	if (promptstring)
		term_putstr(promptstring);
	else
		sh_print_prompt();
}
