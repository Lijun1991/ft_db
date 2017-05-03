/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   db_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: varnaud <varnaud@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/02 20:56:38 by varnaud           #+#    #+#             */
/*   Updated: 2017/05/03 00:11:18 by varnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_db.h"

void	free_cmd(t_cmd *cmd)
{
	int		i;

	if (cmd)
	{
		i = 0;
		if (cmd->argv)
		{
			while (cmd->argv[i])
				free(cmd->argv[i++]);
			free(cmd->argv);
		}
		free(cmd);
	}
}

int		db_exec(t_db *db, t_cmd *cmd)
{
	int		success;

	success = 0;
	if (!cmd || !cmd->argv[0])
		success = 1;
	if (!strcmp(cmd->argv[0], "create"))
		success = db_create(db, parse_entry(cmd));
	else if (!strcmp(cmd->argv[0], "read"))
		;
	else if (!strcmp(cmd->argv[0], "update"))
		;
	else if (!strcmp(cmd->argv[0], "delete"))
		;
	else if (!strcmp(cmd->argv[0], "populate"))
		success = populate(db);
	else
	{
		usage();
		success = 1;
	}
	free_cmd(cmd);
	return (success);
}
