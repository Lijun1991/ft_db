/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: varnaud <varnaud@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/23 23:42:22 by varnaud           #+#    #+#             */
/*   Updated: 2017/04/18 21:25:25 by varnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "gnl.h"

static void	increment_buf(t_fd *f)
{
	char	*new;
	int		i;

	f->size *= 2;
	new = malloc(sizeof(char) * f->size);
	i = 0;
	while (f->buf[i])
	{
		new[i] = f->buf[i];
		i++;
	}
	new[i] = '\0';
	f->i = i;
	free(f->buf);
	f->buf = new;
}

static int	read_fd(t_fd *f, char **line)
{
	int		i;
	int		b;

	if (!(i = 0) && f->i + BUFF_SIZE >= f->size)
		increment_buf(f);
	while (f->buf[i] && f->buf[i] != '\n')
		i++;
	if (f->buf[i] == '\n' && (b = -1))
	{
		*line = malloc(sizeof(char) * (i + 1));
		while (++b < i)
			(*line)[b] = f->buf[b];
		(*line)[i] = '\0';
		b = 0;
		while ((f->buf[b] = f->buf[++i]))
			b++;
		return ((f->i = b) || 1);
	}
	if ((b = read(f->fd, &f->buf[f->i], BUFF_SIZE)) == -1 || !b)
		return (b);
	f->i += b;
	return ((f->buf[f->i] = '\0') || read_fd(f, line));
}

static t_fd	*add_fd(t_fd **list, int fd)
{
	t_fd	*new;

	new = malloc(sizeof(t_fd));
	new->size = BUFF_SIZE + 1;
	new->buf = malloc(sizeof(char) * new->size);
	new->buf[0] = '\0';
	new->fd = fd;
	new->i = 0;
	new->next = *list;
	*list = new;
	return (new);
}

static t_fd	*get_or_rm_fd(t_fd **l, int fd, int del)
{
	t_fd	*previous;
	t_fd	*head;

	head = *l;
	previous = head;
	while (head)
	{
		if (head->fd == fd)
		{
			if (del)
			{
				previous->next = head->next;
				if (head->fd == (*l)->fd)
					*l = (*l)->next;
				free(head->buf);
				free(head);
				break ;
			}
			else
				return (head);
		}
		previous = head;
		head = head->next;
	}
	return (NULL);
}

int			gnl(const int fd, char **line)
{
	static t_fd	*list;
	t_fd		*current;
	int			r;
	int			i;

	if (fd < 0)
		return (fd == -42 ? free_gnl(&list) : -1);
	if (!(current = get_or_rm_fd(&list, fd, 0)))
		current = add_fd(&list, fd);
	r = read_fd(current, line);
	if (r == 0 && current->buf[0])
	{
		i = 0;
		while (current->buf[i])
			i++;
		*line = malloc(sizeof(char) * (++i));
		while (--i >= 0)
			(*line)[i] = current->buf[i];
		current->buf[0] = '\0';
		return (1);
	}
	else if (r == 0)
		get_or_rm_fd(&list, fd, 1);
	return (r);
}
