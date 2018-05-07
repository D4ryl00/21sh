/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbero <rbarbero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/26 09:30:47 by rbarbero          #+#    #+#             */
/*   Updated: 2018/04/24 14:15:33 by rbarbero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "get_next_line.h"
#include <stdlib.h>
#include <unistd.h>

static t_list	*init_bufs(t_list **bufs, const int fd)
{
	t_list	*node;

	node = *bufs;
	while (node)
	{
		if (((t_buff *)(node)->content)->fd == fd)
			return (node);
		node = node->next;
	}
	if (!(node = ft_lstnew(NULL, 0))
			|| !(node->content = malloc(sizeof(t_buff))))
		return (NULL);
	node->content_size = sizeof(t_buff);
	((t_buff *)node->content)->fd = fd;
	((t_buff *)node->content)->lchar = NULL;
	((t_buff *)node->content)->count_nl = 0;
	ft_lstadd(bufs, node);
	return (node);
}

static void		lstdestroy(t_list **lchar)
{
	t_list	*tmp;

	tmp = *lchar;
	*lchar = (*lchar)->next;
	free(tmp->content);
	ft_lstdelone(&tmp, NULL);
}

static int		pop_buf(char **line, t_list **lchar)
{
	t_list	*tmp;
	size_t	len;
	int		i;

	if (lchar && *lchar && ((len = 0) == 0))
	{
		tmp = *lchar;
		while (tmp && *(char *)tmp->content != '\n')
		{
			len++;
			tmp = tmp->next;
		}
		if (!(*line = (char *)ft_memalloc(len + 1)))
			return (-1);
		i = -1;
		while (*lchar && *(char *)(*lchar)->content != '\n')
		{
			(*line)[++i] = *(char *)(*lchar)->content;
			lstdestroy(lchar);
		}
		if (*lchar)
			lstdestroy(lchar);
		return (1);
	}
	return (0);
}

static ssize_t	fill_buffer(t_list *node, const int fd)
{
	ssize_t	ret;
	char	buffer[BUFF_SIZE];
	int		i;

	while ((ret = read(fd, buffer, BUFF_SIZE)))
	{
		if (ret == -1)
			return (ret);
		i = -1;
		while (++i < ret)
		{
			if (!ft_lstpushback(&((t_buff *)node->content)->lchar,
					(void *)&buffer[i], sizeof(char)))
				return (-1);
			((t_buff *)node->content)->count_nl += buffer[i] == '\n' ? 1 : 0;
		}
		if (((t_buff *)node->content)->count_nl)
			break ;
	}
	return (ret);
}

int				get_next_line(const int fd, char **line)
{
	static t_list	*bufs = NULL;
	t_list			*node;
	ssize_t			ret;

	ret = 0;
	if (!(node = init_bufs(&bufs, fd)))
		return (-1);
	if (!(((t_buff *)node->content)->count_nl))
		if ((ret = fill_buffer(node, fd)) == -1)
			return (-1);
	if (((t_buff *)node->content)->count_nl
			|| (!ret && ((t_buff *)node->content)->lchar))
	{
		((t_buff *)node->content)->count_nl--;
		return (pop_buf(line, &(((t_buff *)node->content)->lchar)));
	}
	return (0);
}
