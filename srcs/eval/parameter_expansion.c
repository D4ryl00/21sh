/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parameter_expansion.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbero <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/23 11:20:19 by rbarbero          #+#    #+#             */
/*   Updated: 2019/10/23 17:46:47 by rbarbero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "sh.h"
#include "eval.h"

/*
** input is like $name at beginning
*/

static int	remplace_value(const char **input, t_buf *buf)
{
	int		status;
	t_buf	buf_name;
	char	*value;

	status = 0;
	if (ft_isdigit(*(++(*input))))
	{
		(*input)++;
		return (0);
	}
	if (ft_buf_init(&buf_name) == -1)
		return_perror(ENOMEM, 0, -1);
	while (**input == '_' || ft_isalnum(**input))
	{
		if (ft_buf_add_char(&buf_name, *((*input)++)) == -1)
		{
			ft_perror(ENOMEM, NULL, 0);
			status = -1;
			break ;
		}
	}
	if ((status != -1) && (ft_buf_add_char(&buf_name, '\0') == -1))
	{
		ft_perror(ENOMEM, NULL, 0);
		status = -1;
	}
	else if (status != -1)
	{
		if ((value = env_get_value(buf_name.buf))
				&& (ft_buf_add_str(buf, value) == -1))
		{
			ft_perror(ENOMEM, NULL, 0);
			status = -1;
		}
	}
	ft_buf_destroy(&buf_name);
	return (status);
}

static int	parse_input(const char *input, t_buf *buf)
{
	int	quoted;

	quoted = 0;
	while (*input)
	{
		if (*input == '\\')
		{
			if (ft_buf_add_nstr(buf, (char *)input, 2) == -1)
				return_perror(ENOMEM, NULL, -1);
			input += 2;
		}
		else if (*input == '\'')
		{
			quoted ^= 1;
			if (ft_buf_add_char(buf, *(input++)) == -1)
				return_perror(ENOMEM, NULL, -1);
		}
		else if ((*input == '$') && !quoted)
		{
			if (remplace_value(&input, buf) == -1)
				return (-1);
		}
		else if (ft_buf_add_char(buf, *(input++)) == -1)
				return_perror(ENOMEM, NULL, -1);
	}
	return (0);
}

int	parameter_expansion(t_list *node)
{
	int			status;
	t_buf		buf;
	char		*res;

	if (ft_buf_init(&buf) == -1)
		return_perror(ENOMEM, NULL, -1);
	status = 0;
	if ((status = parse_input((const char *)node->content, &buf)) == -1)
		return (-1);
	if (status != -1 && !(res = ft_buf_flush(&buf)))
	{
		ft_perror(ENOMEM, NULL, 0);
		status = -1;
	}
	if (status != -1)
	{
		free(node->content);
		node->content = res;
		node->content_size = sizeof(char) * (ft_strlen(res) + 1);
	}
	ft_buf_destroy(&buf);
	return (status);
}
