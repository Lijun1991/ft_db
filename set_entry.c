/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_entry.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: varnaud <varnaud@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/02 13:26:20 by varnaud           #+#    #+#             */
/*   Updated: 2017/05/04 00:03:52 by varnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_db.h"

t_data			*add_data(const char *key, const char *value, t_data ***cur)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	memset(data, 0, sizeof(t_data));
	data->key = strdup(key);
	if (value && value[0])
		data->value = strdup(value);
	**cur = data;
	*cur = &(**cur)->next;
	return (data);
}

static void		set_piscine(char *line, t_data ***cur)
{
	char	**s1;
	char	*piscine;
	char	*month;
	char	*year;
	int		i;

	piscine = NULL;
	month = NULL;
	year = NULL;
	s1 = ft_strsplit(line, ',');
	if (s1)
	{
		i = 0;
		while (s1[i])
		{
			if (!month && strncmp(s1[i], "ou=", 3) == 0 &&
											strcmp(&s1[i][3], "people") != 0)
				month = strdup(&s1[i][3]);
			else if (!year && strncmp(s1[i], "ou=", 3) == 0 &&
											strcmp(&s1[i][3], "people") != 0)
				year = strdup(&s1[i][3]);
			free(s1[i++]);
		}
		free(s1);
	}
	if (month || year)
		piscine = ft_strcjoin(month, year, ' ');
	if (month)
		free(month);
	if (year)
		free(year);
	add_data("piscine", piscine, cur);
	free(piscine);
}

static void		set_picture(int fd, char **line, t_data ***cur)
{
	char	*pic;
	char	*tmp;
	int		r;

	pic = strdup(&(*line)[12]);
	free(*line);
	while ((r = gnl(fd, line)) && r != -1)
	{
		if ((*line)[0] == ' ')
		{
			tmp = pic;
			pic = ft_strjoin(pic, &(*line)[1]);
			free(tmp);
		}
		else
			break ;
		free(*line);
	}
	add_data("picture", pic, cur);
	free(pic);
}

t_entry			*get_entry(void)
{
	t_data		**cur;
	t_entry		*entry;
	int			fd;
	int			r;
	char		*line;

	if ((fd = open("tmp_uidinfo", O_RDONLY)) == -1)
		return (NULL);
	entry = malloc(sizeof(t_entry));
	memset(entry, 0, sizeof(t_entry));
	cur = &entry->data;
	while ((r = gnl(fd, &line)) && r != -1)
	{
		pic:
		if (!(line[0] == '#' || line[0] == '\0' || !strchr(line, ':')))
		{
			if (!strncmp(line, "dn:", 3))
				set_piscine(line, &cur);
			else if (!strncmp(line, "cn:", 3))
				add_data("name", &line[4], &cur);
			else if (!entry->id && !strncmp(line, "uid:", 4))
				entry->id = strdup(&line[5]);
			else if (!strncmp(line, "alias:", 6))
				add_data("email", &line[7], &cur);
			else if (!strncmp(line, "mobile:", 7))
				add_data("mobile", &line[8], &cur);
			else if (!strncmp(line, "jpegPhoto:", 8))
			{
				set_picture(fd, &line, &cur);
				GOTO(pic);
			}
		}
		free(line);
	}
	close(fd);
	//unlink("tmp_uidinfo");
	return (entry);
}
