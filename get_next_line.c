/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjuana <tjuana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/02 14:44:34 by tjuana            #+#    #+#             */
/*   Updated: 2019/05/04 19:03:15 by tjuana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <libc.h>

static t_gnl	*gnl_find_or_create(const int fd, t_list **my_list)
{
	t_list	*fl;
	t_gnl	fl_data;

	fl = *my_list;
	while (fl)
	{
		if (((t_gnl *)(fl->content))->fd == fd)
			return (fl->content);
		fl = fl->next;
	}
	fl_data.fd = fd;
	if ((fl_data.buff = ft_strnew(BUFF_SIZE)) == NULL)
		return (NULL);
	if ((fl = ft_lstnew(&fl_data, sizeof(fl_data))) == NULL)
		return (NULL);
	ft_lstadd(my_list, fl);
	return ((*my_list)->content);
}

static ssize_t	gnl_read_line(t_gnl *fl)
{
	char		buff[BUFF_SIZE + 1];
	ssize_t		r;
	char		*temp;

	r = 1;
	while (ft_strstr(fl->buff, "\n") == NULL && \
	(r = read(fl->fd, &buff, BUFF_SIZE)) > 0)
	{
		buff[r] = '\0';
		temp = fl->buff;
		fl->buff = ft_strjoin(fl->buff, buff);
		ft_strdel(&temp);
	}
	return (r);
}

int				get_next_line(const int fd, char **line)
{
	static t_list	*my_list;
	t_gnl			*fl;
	ssize_t			r;
	char			*temp;
	int				endl;

	if (fd < 0 || !line)
		return (-1);
	fl = gnl_find_or_create(fd, &my_list);
	if ((r = gnl_read_line(fl)) == -1)
		return (-1);
	temp = fl->buff;
	if ((endl = (ft_strchr(fl->buff, '\n') > 0)))
		*line = ft_strsub(fl->buff, 0, ft_strchr(fl->buff, '\n') - fl->buff);
	else
		*line = ft_strdup(fl->buff);
	fl->buff = ft_strsub(fl->buff, (unsigned int)(ft_strlen(*line) + endl),
			(size_t)(ft_strlen(fl->buff) - (ft_strlen(*line) + endl)));
	ft_strdel(&temp);
	return (!(!(**line) && !r));
}
