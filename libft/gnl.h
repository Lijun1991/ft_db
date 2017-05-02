/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: varnaud <varnaud@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/23 23:43:03 by varnaud           #+#    #+#             */
/*   Updated: 2017/04/18 21:25:21 by varnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GNL_H
# define GNL_H
# define BUFF_SIZE 1024

typedef struct	s_fd
{
	int			fd;
	int			i;
	int			size;
	char		*buf;
	struct s_fd	*next;
}				t_fd;

int				free_gnl(t_fd **list);

#endif
