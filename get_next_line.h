/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjuana <tjuana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/02 14:40:54 by tjuana            #+#    #+#             */
/*   Updated: 2019/05/04 19:01:08 by tjuana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include "libft/libft.h"
# define BUFF_SIZE 1024

typedef struct	s_gnl
{
	char		*buff;
	int			fd;
}				t_gnl;

int				get_next_line(const int fd, char **line);

#endif
