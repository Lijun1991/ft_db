/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_entry.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: varnaud <varnaud@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/02 13:26:20 by varnaud           #+#    #+#             */
/*   Updated: 2017/05/04 23:52:13 by varnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_db.h"

static void		set_piscine(char *line, t_data ***cur, int i)
{
	char	**s1;
	char	*piscine;
	char	*tmp;

	piscine = NULL;
	s1 = ft_strsplit(line, ',');
	while (s1[i])
	{
		if (!ft_strncmp(s1[i], "ou=", 3) && ft_strcmp(&s1[i][3], "people"))
		{
			if (piscine)
			{
				tmp = piscine;
				piscine = ft_strcjoin(piscine, &s1[i][3], ' ');
				free(tmp);
			}
			else
				piscine = ft_strdup(&s1[i][3]);
		}
		free(s1[i++]);
	}
	free(s1);
	add_data("piscine", piscine, cur);
	free(piscine);
}

static void		set_picture(int fd, char **line, t_data ***cur)
{
	char	*pic;
	char	*tmp;
	int		r;

	pic = ft_strdup(&(*line)[12]);
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

static void		parse_line(int fd, char **line, t_entry *entry, t_data ***cur)
{
	if (!((*line)[0] == '#' || (*line)[0] == '\0' || !strchr((*line), ':')))
	{
		if (!ft_strncmp((*line), "dn:", 3))
			set_piscine((*line), cur, 0);
		else if (!ft_strncmp((*line), "cn:", 3))
			add_data("name", &(*line)[4], cur);
		else if (!entry->id && !ft_strncmp((*line), "uid:", 4))
			entry->id = strdup(&(*line)[5]);
		else if (!ft_strncmp((*line), "alias:", 6))
			add_data("email", &(*line)[7], cur);
		else if (!ft_strncmp((*line), "mobile:", 7))
			add_data("mobile", &(*line)[8], cur);
		else if (!ft_strncmp((*line), "jpegPhoto:", 8))
		{
			set_picture(fd, line, cur);
			parse_line(fd, line, entry, cur);
		}
	}
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
	ft_memset(entry, 0, sizeof(t_entry));
	cur = &entry->data;
	while ((r = gnl(fd, &line)) && r != -1)
	{
		parse_line(fd, &line, entry, &cur);
		free(line);
	}
	close(fd);
	return (entry);
}
