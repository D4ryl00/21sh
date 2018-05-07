/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbero <rbarbero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/18 11:39:41 by rbarbero          #+#    #+#             */
/*   Updated: 2018/05/05 12:10:56 by rbarbero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"
#include "libft.h"

int	prompt(t_input *input, char *prompt)
{
	int	ret;
	if (prompt)
		ft_putstr(prompt);
	else
		ft_putstr("21sh> ");
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
