/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwang <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/01 21:17:59 by lwang             #+#    #+#             */
/*   Updated: 2017/05/02 01:39:33 by lwang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_db.h"

char	*get_path(char *path, char *name)
{
	char *dst;

	dst = ft_strjoin(path, "/");
	dst = ft_strjoin(dst, name);
	return (dst);
}

char		*get_key(char *line, int i)
{
	char	**dst;

	dst = ft_strsplit(line, ':');
	if (i == 1)
		return (dst[0]);
	else if (i == 2)
		return (dst[1]);
	else
		return (NULL);
}

t_data		*new_lst(char *key, char *value)
{
	t_data	*new;

	new = (t_data*)malloc(sizeof(t_data));
	if (!new)
		return (NULL);
	if (!key)
	{
		new->key = NULL;
		new->value = NULL;
	}
	else
	{
		new->key = strdup(key);
		new->value = strdup(value);
	}
	new->next = NULL;
	return (new);
}

char		*check_id_exit(t_db *db, char *id)
{
	struct stat sb;
	char		*newpath;

	newpath = get_path(db->path, id);
	if (stat(newpath, &sb) != -1)
		return (newpath);
	else
		return (NULL);
}

t_entry		*db_read(t_db *db, char *id)
{
	int		fd;
	char	*line;
	t_entry	*dst;
	t_data	**cur;
	char	*newpath;

	dst = (t_entry*)malloc(sizeof(t_entry));
	memset(dst, 0, sizeof(t_entry));
	cur = &dst->data;
	newpath = check_id_exit(db, id);
	fd = open(newpath, O_RDONLY);
	if (fd == -1)
	{
		perror("fd fail");
		return (NULL);
	}
	dst->id = ft_strdup(id);
	while (gnl(fd, &line))
	{
		*cur = new_lst(get_key(line, 1), get_key(line, 2));
		cur = &(*cur)->next;
		free(line);
	}
	close(fd);
	return (dst);
}

int			main(int ac, char **av)
{
	t_db db;
	t_entry	*result;
	t_data	*cur;

	if (ac !=2)
		return (1);
	db.path = strdup("/nfs/2016/l/lwang/ft_db/db");
	result = db_read(&db, av[1]);//db, lwang
	cur = result->data;
	while (cur)
	{
		ft_printf("%s:%s\n", cur->key, cur->value);
		cur = cur->next;
	}
	return (0);
}















