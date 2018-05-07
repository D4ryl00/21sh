/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buf_tools.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbero <rbarbero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/04 13:11:33 by rbarbero          #+#    #+#             */
/*   Updated: 2018/04/02 00:40:34 by rbarbero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_vsdprintf.h"
#include "libft.h"
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

UCHAR		buf_add_str(t_buffer *buf, char *str)
{
	size_t	len;
	t_seq	seq;

	seq.str = str;
	len = ft_strlen(str);
	seq.len = len;
	if (!ft_lstpushback(&(buf->seq), (void *)&seq, sizeof(t_seq)))
		return (0);
	return (1);
}

UCHAR		buf_add_seq(t_buffer *buf, t_seq *seq)
{
	if (!seq)
		return (0);
	if (!ft_lstpushback(&(buf->seq), (void *)seq, sizeof(t_seq)))
		return (0);
	free(seq);
	return (1);
}

static void	seq_del(void *content, size_t content_size)
{
	free(((t_seq *)content)->str);
	((t_seq *)content)->str = NULL;
	free(content);
	(void)content_size;
}

static int	get_len_buf(t_buffer *buf)
{
	t_seq	*seq;
	t_list	*p;
	int		size;

	size = 0;
	p = buf->seq;
	while (p)
	{
		seq = p->content;
		size += seq->len;
		p = p->next;
	}
	return (size);
}

UCHAR		buf_print(char **str, int fd, t_buffer *buf)
{
	t_seq	*seq;

	if (str && !(*str = (char *)ft_memalloc(sizeof(char)
					* (get_len_buf(buf) + 1))))
		return (0);
	while (buf->seq)
	{
		seq = buf->seq->content;
		if (str)
			ft_strncpy(&((*str)[buf->n]), seq->str, seq->len);
		if (fd > -1)
			write(fd, seq->str, seq->len);
		buf->n += seq->len;
		ft_lstdelnode(&(buf->seq), buf->seq, seq_del);
	}
	return (1);
}
