/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   populate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: varnaud <varnaud@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/01 21:12:15 by varnaud           #+#    #+#             */
/*   Updated: 2017/05/02 14:19:18 by varnaud          ###   ########.fr       */
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
			curentry = &(*curentry)->next;
		}
		else
			return (-1);
		cur = lst;
		lst = lst->next;
		free(cur->uid);
		free(cur);
	}
	display_entry(lst);
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

void	display_entry(t_entry *lst)
{
	t_data	*c;

	while (lst)
	{
		printf("%d:\n", lst->id);
		c = lst->data;
		while (c)
		{
			if (strcmp(c->key, "picture"))
				;
			printf("%s: %s\n", c->key, c->value);
		}
	}
}

int		main(int argc, char **argv, char **env)
{
	if (populate())
	{
		printf("RIP\n");
		exit(1);
	}
}
