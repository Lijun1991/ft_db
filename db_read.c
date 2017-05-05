/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   db_read.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwang <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/01 21:17:59 by lwang             #+#    #+#             */
/*   Updated: 2017/05/05 15:38:23 by varnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_db.h"

static void		*cleanup(t_entry *lst, char *line, int fd, char *newpath)
{
	free_entry(lst);
	if (line)
		free(line);
	if (fd > 0)
		close(fd);
	if (newpath)
		free(newpath);
	return (NULL);
}

static t_data	*parse_line(char *line)
{
	char	*p;
	t_data	*data;

	if ((p = ft_strchr(line, ':')) && p > line && !ft_strchr(p + 1, ':'))
	{
		data = malloc(sizeof(t_data));
		data->next = NULL;
		data->key = ft_strndup(line, p - line);
		data->value = ft_strdup(p + 1);
		return (data);
	}
	return (NULL);
}

int				check_id_exist(t_db *db, char *id, char **buf)
{
	struct stat sb;
	char		*newpath;

	newpath = ft_strcjoin(db->path, id, '/');
	if (stat(newpath, &sb) != -1)
	{
		if (buf)
		{
			*buf = newpath;
			return (1);
		}
		free(newpath);
		return (1);
	}
	free(newpath);
	return (0);
}

static t_entry	*read_file(char *path, t_entry *entry)
{
	int		fd;
	int		r;
	char	*line;
	t_entry	*dst;
	t_data	**cur;

	dst = (t_entry*)malloc(sizeof(t_entry));
	ft_memset(dst, 0, sizeof(t_entry));
	cur = &dst->data;
	if ((fd = open(path, O_RDONLY)) == -1)
	{
		ft_fprintf(2, "Unable to open file: %s.\n", path);
		return (cleanup(dst, NULL, 0, NULL));
	}
	dst->id = ft_strdup(entry->id);
	while ((r = gnl(fd, &line)) && r != -1)
	{
		*cur = parse_line(line);
		if (*cur == NULL)
			return (cleanup(dst, NULL, fd, NULL));
		cur = &(*cur)->next;
		free(line);
	}
	close(fd);
	return (dst);
}

t_entry			*db_read(t_db *db, t_entry *entry)
{
	t_entry	*dst;
	char	*newpath;

	if (entry == NULL || entry->id == NULL)
	{
		ft_fprintf(2, "Entry invalid.\n");
		return (NULL);
	}
	if (!check_id_exist(db, entry->id, &newpath))
	{
		ft_fprintf(2, "%s: entry does not exist.\n", entry->id);
		return (NULL);
	}
	if (get_file_size(newpath) > MAX_ENTRY_SIZE)
	{
		free(newpath);
		ft_fprintf(2, "%s: entry is too large, please delete it.\n", entry->id);
		return (NULL);
	}
	dst = read_file(newpath, entry);
	cleanup(NULL, NULL, 0, newpath);
	return (dst);
}
