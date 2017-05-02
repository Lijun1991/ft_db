/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   populate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: varnaud <varnaud@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/01 21:12:15 by varnaud           #+#    #+#             */
/*   Updated: 2017/05/02 00:17:56 by varnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_db.h"

t_uid	*get_uids(void)
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
					if (strcmp(av[i], "memberUid") == 0 && av[i + 1] && av[i + 1][0])
					{
						*cur = malloc(sizeof(t_uid));
						(*cur)->uid = strdup(&av[i + 1][1]);
						(*cur)->next = NULL;
						cur = &(*cur)->next;
					}
					while (av[i])
						free(av[i++]);
				}
				free(av);
			}
			free(line);
		}
		close(fd);
		gnl(-42, NULL);
	}
	else
		return (NULL);
	//unlink("tmp_uids");
	return (lst);
}

t_entry	*set_entry(void)
{
	int		fd;
	char	**av;
	char	**s1;
	char	**s2;
	int		r;
	int		i;
	char	*line;
	t_entry	*entry;
	t_data	*data;
	char	*domaine;
	char	*month;
	char	*year;

	entry = malloc(sizeof(t_entry));
	entry->next = NULL;
	fd = open("tmp_uidinfo", O_RDONLY);
	while ((r = gnl(fd, &line)) && r != -1)
	{
		if (line[0] == '#' || line[0] == '\0')
		{
			free(line);
			continue ;
		}
		av = ft_strsplit(line, ':');
		if (av)
		{
			if (av[0])
			{
				if (strcmp(av[0], "dn") == 0 && av[1])
				{
					s1 = ft_strsplit(av[i + 1], ',');
					if (s1)
					{
						i = 0;
						month = NULL;
						year = NULL;
						domaine = NULL;
						while (s1[i])
						{
							if (strncmp(s1[i], "uid=", 4) == 0)
								entry->id = strdup(&s1[i][5]);
							else if (!month && strncmp(s1[i], "ou=") == 0 &&
										strcmp(&s1[i][4], "people") != 0)
								month = strdup(&s1[i][4]);
							else if (!year && strncmp(s1[i], "ou=") == 0 &&
										strcmp(&s1[i][4], "people") != 0)
								year = strdup(&s1[i][4]);
							else if (strncmp(s1[i], "dc=42") == 0)
								domain = strdup("42.us.org");
							free(s1[i]);
						}
						
						free(month);
						free(year);
						free(domaine);
						free(s1);
					}
				}
				i = 0;
				while (av[i])
					free(av[i++]);
			}
			free(av);
		}
		free(line);
	}
	close(fd);
	unlink("tmp_uidinfo");
	return (entry);
}

int		populate(void)
{
	t_uid	*lst;
	t_uid	*cur;
	int		fd;
	pid_t	pid;
	char	**av;
	char	*path;
	int		status;
	char	*line;
	char	**splt;
	int		r;
	int		i;
	t_entry	*entry;
	t_entry	**curentry;

	lst = get_uids();
	if (lst == NULL)
		return (1);
	entry = NULL;
	curentry = &entry;
	while (lst)
	{
		status = 0;
		pid = fork();
		if (pid == 0)
		{
			fd = open("tmp_uidinfo", O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
			dup2(fd, 1);
			close(fd);
			av = malloc(sizeof(char*) * 4);
			av[0] = strdup("/usr/bin/ldapsearch");
			av[1] = strdup("-x");
			av[3] = ft_strjoin("uid=", lst->uid);
			av[4] = NULL;
			execve("/usr/bin/ldapsearch", av, NULL);
			exit(1);
		}
		else if (pid > 0)
		{
			wait(&status);
			if (status)
				return (-1);
			*curentry = set_entry();

		}
		else
			return (-1);
		cur = lst;
		lst = lst->next;
		free(cur->uid);
		free(cur);
	}
	return (0);
	/*
	int		fd;
	pid_t	pid;
	char	**av;

	pid = fork();
	if (pid == 0)
	{
		fd = open("tmp_db", O_RDWR | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
		dup2(fd, 1);
		close(fd);
		av = malloc(sizeof(char*) * 3);
		av[0] = strdup("/usr/bin/ldapsearch");
		av[1] = strdup("-x");
		av[2] = NULL;
		execve("/usr/bin/ldapsearch", av, NULL);
		perror("exec");
		exit(1);
	}
	else if (pid > 0)
		wait(0);
	else
		return(1);
	return (0);
	*/
}

int		main(int argc, char **argv, char **env)
{
	if (populate())
	{
		printf("RIP\n");
		exit(1);
	}
}
