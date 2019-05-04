/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjuana <tjuana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/02 14:44:34 by tjuana            #+#    #+#             */
/*   Updated: 2019/05/04 17:04:44 by tjuana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <libc.h>

static t_gnl	*gnl_find_or_create(const int fd, t_list **my_list)
{
	t_list	*file;
	t_gnl	file_data;

	file = *my_list;
	while (file)
	{
		if (((t_gnl *)(file->content))->fd == fd)
			return (file->content);
		file = file->next;
	}
	file_data.fd = fd;
	if ((file_data.buff = ft_strnew(BUFF_SIZE)) == NULL)
		return (NULL);
	if ((file = ft_lstnew(&file_data, sizeof(file_data))) == NULL)
		return (NULL);
	ft_lstadd(my_list, file);
	return ((*my_list)->content);
}

static ssize_t	gnl_read_line(t_gnl *file)
{
	char		buff[BUFF_SIZE + 1];
	ssize_t		r;
	char		*temp;

	r = 1;
	while (r && ft_strstr(file->buff, "\n") == NULL)
	{
		r = read(file->fd, &buff, BUFF_SIZE);
		temp = file->buff;
		if (r == -1)
			return (-1);
		buff[r] = '\0';
		file->buff = ft_strjoin(file->buff, buff);
		ft_strdel(&temp);
	}
	return (r);
}

int				get_next_line(const int fd, char **line)
{
	static t_list	*my_list;
	t_gnl			*file;
	ssize_t			r;
	char			*temp;

	if (fd < 0 || !line)
		return (-1);
	file = gnl_find_or_create(fd, &my_list);
	if ((r = gnl_read_line(file)) == -1)
		return (-1);
	temp = file->buff;
	*line = ft_strcdup(file->buff, '\n');
	file->buff = ft_strdup(file->buff + ft_strclen(file->buff, '\n') + 1);
	ft_strdel(&temp);
	return (**line || r > 0 ? 1 : 0);
}

int main(int argc, char **argv)
{
    int fd;
    char *line;

    if (argc == 1)
        fd = 0;
    else if (argc == 2)
        fd = open(argv[1], O_RDONLY);
    else
        return (2);
    while (get_next_line(fd, &line) == 1)
    {
       // ft_putendl(line);
        ft_strdel(&line);
    }
    if (argc == 2)
    close(fd);
}
