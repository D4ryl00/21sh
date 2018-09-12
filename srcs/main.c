/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amordret <amordret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/18 11:39:41 by rbarbero          #+#    #+#             */
/*   Updated: 2018/09/12 16:56:49 by rbarbero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"
#include "libft.h"

int		newprompt(t_input *input, char *promptstring)
{
	prompt(promptstring);
	return (read_input(input));
}

int		main(int argc, char **argv, char **environ)
{
	t_input			input;
	t_ast_program	*program;

	(void)argc;
	(void)argv;
	(void)environ;
	program = NULL;
	ft_set_term();
	while (42)
	{
		newprompt(&input, NULL);
		if (!(program = eval(&input)))
			continue;
	}
	termcaps_reset_term_and_exit();
	return (0);
}
