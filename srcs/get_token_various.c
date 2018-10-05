/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_token_various.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbero <rbarbero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/18 14:24:53 by rbarbero          #+#    #+#             */
/*   Updated: 2018/10/05 22:27:16 by rbarbero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "sh.h"

int	comment_input(t_input *input)
{
	while (*(input->str) && *(input->str) != '\n')
		(input->str)++;
	return (0);
}

int	delimiter_case(t_list **tokens, t_buf *buffer, t_input *input,
		unsigned char f_params[2])
{
	char	*word;

	if (f_params[0] || f_params[1])
	{
		if (!(word = ft_buf_flush(buffer)))
			exit_perror(ENOMEM, NULL);
		insert_token(tokens, word, token_get_op_type(word));
		f_params[0] = 0;
		f_params[1] = 0;
	}
	if (*(input->str) == '\n')
	{
		if (!(word = ft_strdup("newline")))
			exit_perror(ENOMEM, NULL);
		insert_token(tokens, word, NEWLINE);
	}
	(input->str)++;
	return (0);
}
