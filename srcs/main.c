/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amordret <amordret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/18 11:39:41 by rbarbero          #+#    #+#             */
/*   Updated: 2018/05/09 14:03:49 by amordret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"
#include "libft.h"

void    mainloop(t_input *input, char *promptstring, t_btree *ast)
{
    while (42)
    {
        prompt(promptstring);
        if (read_input(input) > -1)
        {
            ast = eval(ast, input);
        }
    }
}

int     main(int argc, char **argv, char **environ)
{
	t_btree	*ast;
	t_input	input;

	(void)argc;
	(void)argv;
	(void)environ;

	ast = NULL;
    ft_set_term();
    mainloop(&input, NULL, ast);
	return (0);
}
