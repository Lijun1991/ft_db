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

char		*id_line(char *id)
{
	char	*dst;

	dst = ft_strnew(strlen(id) + 3 + 1);
	ft_strcpy(dst, "id:");
	ft_strcpy(dst, id);
	return (dst);
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

void		lst_add(t_data	**data, t_data *new)
{
	new->next = *data;
	*data = new;
}

t_entry		*db_read(char *file, char *id)
{
	int		i;
	int		fd;
	char	*line;
	t_entry	*dst;
	t_data	*new;

	i = 5;//very piece of data have 6 line
	dst = (t_entry*)malloc(sizeof(t_entry));
	fd = open("file", O_RDONLY);
	while (gnl(fd, &line) == 1)
	{
		if (ft_strcmp(line, id_line(id)) == 0)
			break ;
		free(line);
	}
	printf("id line is %s\n", line);
	while (gnl(fd, &line) == 1 && i-- > 0)
	{
		new = new_lst(get_key(line, 1), get_key(line, 2));
		lst_add(&dst->data, new);
	}
	return (dst);
}

int			main(int ac, char **av)
{
	if (ac == 3)
	{
		db_read(av[0], av[1]);//db, lwang
	}
	return (0);

}
