/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   db_read.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwang <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/01 21:17:59 by lwang             #+#    #+#             */
/*   Updated: 2017/05/04 15:39:39 by varnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_db.h"

static int		cleanup(t_entry *lst, char *line, int fd, char *newpath)
{
	free_entry(lst);
	if (line)
		free(line);
	if (fd > 0)
		close(fd);
	if (newpath)
		free(newpath);
	return (1);
}

static t_data	*parse_line(char *line)
{
	char	*p;
	t_data	*data;

	if ((p = strchr(line, ':')) && p > line && !strchr(p + 1, ':'))
	{
		data = malloc(sizeof(t_data));
		data->next = NULL;
		data->key = strndup(line, p - line);
		data->value = strdup(p + 1);
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

int				db_read(t_db *db, t_cmd *cmd)
{
	int		fd;
	char	*line;
	t_entry	*dst;
	t_data	**cur;
	char	*newpath;
	t_entry	*entry;

	if ((entry = parse_entry(cmd)) == NULL || entry->id == NULL)
	{
		ft_fprintf(2, "Entry invalid.\n");
		return (1);
	}
	dst = (t_entry*)malloc(sizeof(t_entry));
	memset(dst, 0, sizeof(t_entry));
	cur = &dst->data;
	if (!check_id_exist(db, entry->id, &newpath))
	{
		ft_fprintf(2, "%s: entry does not exist.\n", entry->id);
		return (1);
	}
	fd = open(newpath, O_RDONLY);
	if (fd == -1)
	{
		ft_fprintf(2, "Unable to open file: %s.\n", newpath);
		return (cleanup(dst, NULL, 0, newpath));
	}
	dst->id = ft_strdup(entry->id);
	while (gnl(fd, &line))
	{
		*cur = parse_line(line);
		if (*cur == NULL)
			return (cleanup(dst, line, fd, newpath));
		cur = &(*cur)->next;
		free(line);
	}//TODO CLEANUP
	display_entry(dst);
	free_entry(dst);
	free_entry(entry);
	free(newpath);
	close(fd);
	return (0);
}
