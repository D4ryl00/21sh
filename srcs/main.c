/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amordret <amordret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/18 11:39:41 by rbarbero          #+#    #+#             */
/*   Updated: 2018/07/30 23:50:51 by rbarbero         ###   ########.fr       */
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
	t_btree	*ast;

	(void)argc;
	(void)argv;
	(void)environ;
	ast = NULL;
	ft_set_term();
	while (42)
	{
		newprompt(&input, NULL);
		if (!(ast = eval(&input)))
			continue;
	}
	termcaps_reset_term_and_exit();
	return (0);
}
