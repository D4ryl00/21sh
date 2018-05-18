/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_token_word.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbero <rbarbero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/18 14:08:34 by rbarbero          #+#    #+#             */
/*   Updated: 2018/05/18 14:30:48 by rbarbero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "sh.h"

int	word_add_char_case(t_buf *buffer, t_input *input)
{
	if (ft_buf_add_char(buffer, *(input->str)) == -1)
		return (return_perror(ENOMEM, NULL));
	(input->str)++;
	return (0);
}

int	word_start_case(t_buf *buffer, t_input *input, unsigned char f_params[2])
{
	if (ft_buf_add_char(buffer, *(input->str)) == -1)
		return (return_perror(ENOMEM, NULL));
	f_params[0] = 1;
	(input->str)++;
	return (0);
}
