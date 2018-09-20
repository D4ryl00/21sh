/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_token_various.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbero <rbarbero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/18 14:24:53 by rbarbero          #+#    #+#             */
/*   Updated: 2018/09/20 11:48:43 by rbarbero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "sh.h"

int	comment_input(t_input *input)
{
	while (*(input->str) && *(input->str) != '\n')
		(input->str)++;
	if (*(input->str))
		(input->str)++;
	return (0);
}

int	delimiter_case(t_list **tokens, t_buf *buffer, t_input *input,
		unsigned char f_params[2])
{
	char	*word;

	if (f_params[0] || f_params[1])
	{
		word = ft_buf_flush(buffer);
		if (insert_token(tokens, word, token_get_op_type(word)) == -1)
			return (return_perror(ENOMEM, NULL));
		f_params[0] = 0;
		f_params[1] = 0;
	}
	(input->str)++;
	return (0);
}
