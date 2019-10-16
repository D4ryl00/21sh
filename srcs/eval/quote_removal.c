/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_removal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbero <rbarbero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/12 18:30:42 by rbarbero          #+#    #+#             */
/*   Updated: 2019/10/16 23:26:03 by rbarbero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "eval.h"

static int	quote(t_buf *buf, const char **in, const char delim)
{
	while (*(++(*in)))
	{
		if (**in == delim)
		{
			(*in)++;
			return (0);
		}
		else if (ft_buf_add_char(buf, **in) == -1)
			return_perror(ENOMEM, NULL, -1);
	}
	return (-1);
}

static int	backslash(t_buf *buf, const char **in)
{
	(*in)++;
	if (**in)
	{
		if (ft_buf_add_char(buf, **in) == -1)
			return_perror(ENOMEM, NULL, -1);
		return (0);
	}
	else
		return (-1);
}

static int	do_quote_removal(t_buf *buf, const char *in)
{
	int	status;

	status = 0;
	while (*in)
	{
		if (*in == '\'')
			status = quote(buf, &in, '\'');
		else if (*in == '"')
			status = quote(buf, &in, '"');
		else if (*in == '\\')
			status = backslash(buf, &in);
		else if (ft_buf_add_char(buf, *(in++)) == -1)
			return_perror(ENOMEM, NULL, -1);
		if (status == -1)
			break ;
	}
	return (status);
}

int			quote_removal(t_list *node)
{
	t_buf	buf;
	int		status;
	char	*tmp;

	status = 0;
	if (ft_buf_init(&buf) == -1)
		return (-1);
	if (!(status = do_quote_removal(&buf, (const char *)node->content)))
	{
		if (!(tmp = ft_buf_flush(&buf)))
		{
			status = -1;
			ft_perror(ENOMEM, NULL, 0);
		}
		else
		{
			free(node->content);
			node->content = tmp;
			node->content_size = sizeof(char) * (ft_strlen(tmp) + 1);
		}
	}
	ft_buf_destroy(&buf);
	return (status);
}
