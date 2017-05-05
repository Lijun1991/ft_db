/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   db_populate.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: varnaud <varnaud@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/01 21:12:15 by varnaud           #+#    #+#             */
/*   Updated: 2017/05/05 01:10:11 by lwang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_db.h"

static void		fetch_file(t_uid *lst)
{
	int		fd;
	int		nll;
	char	**av;

	fd = open("tmp_uidinfo", O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
	nll = open("/dev/null", O_WRONLY);
	dup2(nll, 2);
	dup2(fd, 1);
	close(fd);
	close(nll);
	av = malloc(sizeof(char*) * 4);
	av[0] = ft_strdup("/usr/bin/ldapsearch");
	av[1] = ft_strjoin("uid=", lst->uid);
	av[2] = NULL;
	execve("/usr/bin/ldapsearch", av, NULL);
	exit(1);
}

static int		add_file(int total, int i, t_db *db)
{
	int		status;
	int		len;
	t_entry	*entry;

	wait(&status);
	if (status)
		return (-1);
	status = 0;
	len = ft_numlen(total);
	ft_printf("Getting entry %*d/%*d%c", len, i, len, total,
											i < total ? '\r' : '\n');
	if ((entry = get_entry()) == NULL)
		return (1);
	if (db_create(db, entry))
		status = 1;
	free_entry(entry);
	return (status);
}

static void		next_uid(t_uid **uid)
{
	t_uid	*t;

	t = (*uid)->next;
	free((*uid)->uid);
	free(*uid);
	*uid = t;
}

int				db_populate(t_db *db)
{
	int		i;
	int		total;
	t_uid	*lst;
	pid_t	pid;

	total = 0;
	if ((lst = get_uids(db, &total)) == NULL)
		return (ft_fprintf(2, "No uid to fetch.\n"));
	i = 0;
	while (lst)
	{
		pid = fork();
		if (pid == 0)
			fetch_file(lst);
		else if (pid > 0)
			add_file(total, ++i, db);
		else
			return (-1);
		next_uid(&lst);
	}
	unlink("tmp_uidinfo");
	gnl(-42, NULL);
	return (0);
}
