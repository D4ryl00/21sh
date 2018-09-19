/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amordret <amordret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/18 11:39:41 by rbarbero          #+#    #+#             */
/*   Updated: 2018/09/19 11:30:29 by amordret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"
#include "libft.h"

t_command_history	*g_first_cmd_history = NULL;
t_list				*g_env = NULL;

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
	g_env = ft_strarrtolist(environ);
	program = NULL;
	ft_set_term();
	fill_command_hist();
	while (42)
	{
		newprompt(&input, NULL);
		if (!(program = eval(&input)))
			continue;
	}
	termcaps_reset_term_and_exit();
	return (0);
}
