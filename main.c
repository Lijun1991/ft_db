/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: varnaud <varnaud@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/01 13:17:17 by varnaud           #+#    #+#             */
/*   Updated: 2017/05/03 15:55:39 by varnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_db.h"

static t_db	*set_db(void)
{
	t_db		*db;
	struct stat	s;

	db = malloc(sizeof(t_db));
	memset(db, 0, sizeof(t_db));
	db->path = strdup(getenv("FT_DB_PATH"));
	if (db->path == NULL || stat(db->path, &s) == -1 || !S_ISDIR(s.st_mode) ||
			access(db->path, R_OK | W_OK | X_OK))
	{
		ft_fprintf(2, "Please set FT_DB_PATH environment variable to a valide folder.\n");
		free(db);
		return (NULL);
	}
	return (db);
}

static void	cleanup(t_db *db, t_cmd *cmd)
{
	if (db)
	{
		if (db->path)
			free(db->path);
		free(db);
	}
	free_cmd(cmd);
}

void		usage(void)
{
	ft_fprintf(2, "usage: ft_db [create | read | update | delete | populate] [key:value]...\n");
}

int			main(int argc, char **argv)
{
	t_db	*db;
	t_cmd	*cmd;
	int		success;

	success = 0;
	cmd = NULL;
	db = set_db();
	if (db == NULL)
		exit(1);
	if (argc > 1)
	{
		cmd = parse_argv(argc, argv);
		success = db_exec(db, cmd);
	}
	else
		db_prompt(db);
	cleanup(db, cmd);
	return (success);
}
