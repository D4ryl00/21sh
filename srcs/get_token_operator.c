/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_token_operator.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbero <rbarbero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/18 14:10:21 by rbarbero          #+#    #+#             */
/*   Updated: 2018/05/19 13:22:47 by rbarbero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "sh.h"

int	operator_case(t_list **tokens, t_buf *buffer, t_input *input,
		unsigned char f_params[2])
{
	if (!is_operator(buffer, *(input->str), f_params))
	{
		if (insert_token(tokens, ft_buf_flush(buffer)) == -1)
			return (return_perror(ENOMEM, NULL));
		f_params[1] = 0;
	}
	else
	{
		if (ft_buf_add_char(buffer, *(input->str)) == -1)
			return (return_perror(ENOMEM, NULL));
		(input->str)++;
	}
	return (0);
}

int	operator_start_case(t_list **tokens, t_buf *buffer, t_input *input,
		unsigned char f_params[2])
{
	if (f_params[0] && insert_token(tokens, ft_buf_flush(buffer)) == -1)
			return (return_perror(ENOMEM, NULL));
	if (ft_buf_add_char(buffer, *(input->str)) == -1)
		return (return_perror(ENOMEM, NULL));
	f_params[0] = 0;
	f_params[1] = 1;
	(input->str)++;
	return (0);
}
