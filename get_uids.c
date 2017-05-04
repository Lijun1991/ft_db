/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_uids.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: varnaud <varnaud@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/04 14:36:01 by varnaud           #+#    #+#             */
/*   Updated: 2017/05/04 15:06:27 by varnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_db.h"

static void		fetch_uids(void)
{
	int		fd;
	char	**av;

	fd = open("tmp_uids", O_RDWR | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
	dup2(fd, 1);
	close(fd);
	av = malloc(sizeof(char*) * 5);
	av[0] = strdup("/usr/bin/ldapsearch");
	av[1] = strdup("-x");
	av[2] = strdup("-b");
	av[3] = strdup("cn=_developer,ou=groups,dc=42,dc=us,dc=org");
	av[4] = NULL;
	execve("/usr/bin/ldapsearch", av, NULL);
	exit(1);
}

static t_uid	*parse_line(t_db *db, char *line)
{
	char	**av;
	int		i;
	t_uid	*uid;

	uid = NULL;
	av = ft_strsplit(line, ':');
	if (av)
	{
		if (av[0])
		{
			i = 0;
			if (strcmp(av[i], "memberUid") == 0 && av[i + 1] && av[i + 1][0]
				&& !check_id_exist(db, &av[i + 1][1], NULL))
			{
				uid = malloc(sizeof(t_uid));
				uid->uid = strdup(&av[i + 1][1]);
				uid->next = NULL;
			}
			while (av[i])
				free(av[i++]);
		}
		free(av);
	}
	return (uid);
}

static int		parse_uids(t_uid **cur, t_db *db)
{
	char	*line;
	int		fd;
	int		r;
	int		total;
	int		status;

	total = 0;
	wait(&status);
	if (status)
		return (-1);
	if ((fd = open("tmp_uids", O_RDONLY)) == -1)
		return (-1);
	while ((r = gnl(fd, &line)) && r != -1)
	{
		if ((*cur = parse_line(db, line)))
		{
			total++;
			cur = &(*cur)->next;
		}
		free(line);
	}
	close(fd);
	return (total);
}

t_uid			*get_uids(t_db *db, int *total)
{
	pid_t	pid;
	t_uid	*lst;
	int		t;

	lst = NULL;
	pid = fork();
	if (pid == 0)
		fetch_uids();
	else if (pid > 0)
		t = parse_uids(&lst, db);
	else
		return (NULL);
	if (total)
		*total = t;
	unlink("tmp_uids");
	return (lst);
}
