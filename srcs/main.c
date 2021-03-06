/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amordret <amordret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/18 11:39:41 by rbarbero          #+#    #+#             */
/*   Updated: 2019/10/16 16:21:33 by amordret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"
#include "libft.h"
#include "eval.h"
#include "signals.h"

t_command_history	*g_first_cmd_history = NULL;
t_list				*g_env = NULL;

int		newprompt(t_input *input, char *promptstring)
{
	int	status;

	ft_set_term();
	if (input)
	{
		if (input->save)
		{
			free(input->save);
			input->save = NULL;
			input->str = NULL;
		}
	}
	prompt(promptstring);
	status = read_input(input, promptstring);
	termcaps_reset_term();
	return (status);
}

int		main(int argc, char **argv, char **environ)
{
	t_input	input;
	int		status;

	(void)argc;
	(void)argv;
	input.save = NULL;
	input.str = NULL;
	status = 0;
	g_env = ft_strarrtolist(environ);
	init_s_shell();
	if (signals_init() == -1)
		termcaps_reset_term_and_exit(1);
	fill_command_hist();
	while (42)
	{
		newprompt(&input, NULL);
		if (input.str)
			status = eval(&input);
		else
			ft_putchar('\n');
	}
	termcaps_reset_term_and_exit(0);
	return (status);
}
