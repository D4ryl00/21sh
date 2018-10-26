/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbero <rbarbero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/05 09:46:20 by rbarbero          #+#    #+#             */
/*   Updated: 2018/10/26 15:28:27 by rbarbero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "sh.h"
#include "eval.h"

int	eval_pipeline(t_ast_pipeline *pipeline, unsigned char async)
{
	int	status;

	status = 0;
	if (pipeline->pipe_sequence)
		status = eval_pipe_sequence(pipeline->pipe_sequence, async);
	if (pipeline->bang == '!')
		status = ~status;
	return (status);
}
