/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amordret <amordret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/18 11:39:41 by rbarbero          #+#    #+#             */
/*   Updated: 2018/05/09 11:43:31 by amordret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"
#include "libft.h"

void    sh_print_prompt(void)
{
    char    *pwd;

    if (!(((pwd = getenv("PWD")) == NULL)))
    {
        ft_putstr(PROMPT1);
        ft_putstr(pwd);
        //free(pwd);
    }
    ft_putstr(PROMPT2);
    ft_putstr(PROMPT3);
}

int	prompt(t_input *input, char *prompt)
{
	int	ret;
	if (prompt)
		ft_putstr(prompt);
	else
		sh_print_prompt();
	ret = get_next_line(0, &(input->str));
	input->save = input->str;
	return (ret);
}

int	main(int argc, char **argv, char **environ)
{
	t_btree	*ast;
	t_input	input;

	(void)argc;
	(void)argv;
	(void)environ;
	ast = NULL;
	while (prompt(&input, NULL))
		ast = eval(ast, &input);
	return (0);
}
