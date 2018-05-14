/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amordret <amordret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/18 11:39:41 by rbarbero          #+#    #+#             */
/*   Updated: 2018/05/14 15:34:39 by amordret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"
#include "libft.h"

int    newprompt(t_input *input, char *promptstring)
{
    prompt(promptstring);
    return (read_input(input, 0));
}

int     main(int argc, char **argv, char **environ)
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
        ast = eval(ast, &input);
    }
    termcaps_reset_term_and_exit();
	return (0);
}
