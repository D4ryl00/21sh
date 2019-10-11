/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_file.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amordret <amordret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/17 11:22:17 by amordret          #+#    #+#             */
/*   Updated: 2018/09/19 11:25:34 by amordret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int		open_history_file(char write)
{
	char	*historyfilepath;
	int		fd;

	fd = 0;
	historyfilepath = ft_memalloc(ft_strlen(getenv("HOME")) + 5);
	ft_strcat(historyfilepath, getenv("HOME"));
	ft_strcat(historyfilepath, "/.21sh");
	if (write == 1 || write == 0)
	{
		if ((fd = open(historyfilepath,
		O_RDWR | O_CREAT, S_IRWXG | S_IRWXO | S_IRWXU)) < 1)
			term_putstr(ERR_READ);
	}
	free(historyfilepath);
	return (fd);
}

void	close_history_file(int fd)
{
	if (fd > 1)
		if ((close(fd)) == -1)
			term_putstr(ERR_CLOSE);
}
