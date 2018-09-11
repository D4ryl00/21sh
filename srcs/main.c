/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amordret <amordret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/18 11:39:41 by rbarbero          #+#    #+#             */
/*   Updated: 2018/09/11 22:22:34 by rbarbero         ###   ########.fr       */
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
	t_input	input;
	t_list	*lcmd;

	(void)argc;
	(void)argv;
	(void)environ;
	lcmd = NULL;
	ft_set_term();
	while (42)
	{
		newprompt(&input, NULL);
		if (!(lcmd = eval(&input)))
			continue;
	}
	termcaps_reset_term_and_exit();
	return (0);
}
