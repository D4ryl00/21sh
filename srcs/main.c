/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amordret <amordret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/18 11:39:41 by rbarbero          #+#    #+#             */
/*   Updated: 2018/11/08 17:38:14 by amordret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"
#include "libft.h"
#include "eval.h"

t_command_history	*g_first_cmd_history = NULL;
t_list				*g_env = NULL;

int		newprompt(t_input *input, char *promptstring)
{
	int	status;

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
	ft_set_term();
	fill_command_hist();
	while (42)
	{
		newprompt(&input, NULL);
		status = eval(&input);
	}
	termcaps_reset_term_and_exit(0);
	return (status);
}
