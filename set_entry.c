/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_entry.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: varnaud <varnaud@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/02 13:26:20 by varnaud           #+#    #+#             */
/*   Updated: 2017/05/02 15:12:47 by varnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_db.h"

static char	*set_piscine(char *line)
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
	return (piscine);
}

static char	*set_picture(int fd, char *line)
{
	char	*pic;
	char	*tmp;
	int		r;

	pic = strdup(&line[12]);
	while ((r = gnl(fd, &line)) && r != -1)
	{
		if (line[0] == ' ')
		{
			tmp = pic;
			pic = ft_strjoin(pic, &line[1]);
			free(tmp);
		}
		else
		{
			free(line);
			break ;
		}
		free(line);
	}
	return (pic);
}

static t_entry	*set_entry(t_sample *sample)
{
	t_entry	*entry;
	t_data	*data;
	t_data	**next;

	entry = malloc(sizeof(t_entry));
	entry->id = sample->id;
	entry->next = NULL;
	next = &entry->data;
	// Piscine data
	data = malloc(sizeof(t_data));
	data->key = strdup("piscine");
	data->value = sample->piscine;
	data->next = NULL;
	*next = data;
	next = &data->next;
	// Name data
	data = malloc(sizeof(t_data));
	data->key = strdup("name");
	data->value = sample->name;
	data->next = NULL;
	*next = data;
	next = &data->next;
	// Mobile data
	data = malloc(sizeof(t_data));
	data->key = strdup("mobile");
	data->value = sample->mobile;
	data->next = NULL;
	*next = data;
	next = &data->next;
	// Email data
	data = malloc(sizeof(t_data));
	data->key = strdup("email");
	data->value = sample->email;
	data->next = NULL;
	*next = data;
	next = &data->next;
	// Picture data
	data = malloc(sizeof(t_data));
	data->key = strdup("picture");
	data->value = sample->picture;
	data->next = NULL;
	*next = data;
	return (entry);
}

t_entry		*get_entry(void)
{
	t_sample	sample;
	int			fd;
	int			r;
	char		*line;

	memset(&sample, 0, sizeof(t_sample));
	fd = open("tmp_uidinfo", O_RDONLY);
	while ((r = gnl(fd, &line)) && r != -1)
	{
		if (!(line[0] == '#' || line[0] == '\0' || !strchr(line, ':')))
		{
			if (!strncmp(line, "dn:", 3))
				sample.piscine = set_piscine(line);
			else if (!strncmp(line, "cn:", 3))
				sample.name = strdup(&line[4]);
			else if (!strncmp(line, "uid:", 4))
				sample.id = strdup(&line[5]);
			else if (!strncmp(line, "alias:", 6))
				sample.email = strdup(&line[7]);
			else if (!strncmp(line, "mobile:", 7))
				sample.email = strdup(&line[8]);
			else if (!strncmp(line, "jpegPhoto:", 8))
				sample.picture = set_picture(fd, line);
		}
		free(line);
	}
	close(fd);
	//unlink("tmp_uidinfo");
	return (set_entry(&sample));
}

