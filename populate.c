/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   populate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: varnaud <varnaud@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/01 21:12:15 by varnaud           #+#    #+#             */
/*   Updated: 2017/05/04 13:34:34 by lwang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_db.h"

static t_uid	*get_uids(t_db *db, int *total)
{
	int		fd;
	int		r;
	int		i;
	char	**av;
	char	*line;
	int		status;
	pid_t	pid;
	t_uid	*lst;
	t_uid	**cur;

	lst = NULL;
	cur = &lst;
	pid = fork();
	status = 0;
	if (pid == 0)
	{
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
	else if (pid > 0)
	{
		wait(&status);
		if (status)
			return (NULL);
		fd = open("tmp_uids", O_RDONLY);
		while ((r = gnl(fd, &line)) && r != -1)
		{
			av = ft_strsplit(line, ':');
			if (av)
			{
				if (av[0])
				{
					i = 0;
					if (strcmp(av[i], "memberUid") == 0 && av[i + 1] && av[i + 1][0] && !check_id_exit(db, &av[i + 1][1]))
					{
						*cur = malloc(sizeof(t_uid));
						(*cur)->uid = strdup(&av[i + 1][1]);
						(*cur)->next = NULL;
						cur = &(*cur)->next;
						if (total)
							(*total)++;
					}
					while (av[i])
						free(av[i++]);
				}
				free(av);
			}
			free(line);
			//if (total && *total == 10)
			//	break ;
		}
		close(fd);
	}
	else
		return (NULL);
	unlink("tmp_uids");
	return (lst);
}

int				populate(t_db *db)
{
	int		nll;
	int		i;
	int		total;
	int		len;
	t_uid	*lst;
	t_uid	*cur;
	int		fd;
	pid_t	pid;
	char	**av;
	int		status;
	t_entry	*entry;
	t_entry	**curentry;

	total = 0;
	ft_printf("Getting uids...\n");
	lst = get_uids(db, &total);
	if (lst == NULL)
		return (1);
	len = ft_numlen(total);
	entry = NULL;
	curentry = &entry;
	i = 0;
	ft_printf("Setting entries...\n");
	while (lst)
	{
		status = 0;
		pid = fork();
		if (pid == 0)
		{
			fd = open("tmp_uidinfo", O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
			nll = open("/dev/null", O_WRONLY);
			dup2(nll, 2);
			dup2(fd, 1);
			close(fd);
			close(nll);
			av = malloc(sizeof(char*) * 4);
			av[0] = strdup("/usr/bin/ldapsearch");
			//av[1] = strdup("-x");
			av[1] = ft_strjoin("uid=", lst->uid);
			av[2] = NULL;
			execve("/usr/bin/ldapsearch", av, NULL);
			exit(1);
		}
		else if (pid > 0)
		{
			wait(&status);
			if (status)
				return (-1);
			//printf("Getting entry of: %s\n", lst->uid);
			i++;
			ft_printf("Getting entry %*d/%*d%c", len, i, len, total, i < total ? '\r' : '\n');
			*curentry = get_entry();
			db_create(db, *curentry);
			//display_entry(*curentry);
			//getchar();
			curentry = &(*curentry)->next;
		}
		else
			return (-1);
		cur = lst;
		lst = lst->next;
		free(cur->uid);
		free(cur);
	}
	free_entry(entry);
	unlink("tmp_uidinfo");
	gnl(-42, NULL);
	//display_entries(entry);
	return (0);
}
