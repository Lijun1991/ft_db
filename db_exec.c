/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   db_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: varnaud <varnaud@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/02 20:56:38 by varnaud           #+#    #+#             */
/*   Updated: 2017/05/04 16:25:51 by varnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_db.h"

static int	output_read(t_db *db, t_entry *entry)
{
	int		success;
	t_entry	*result;

	success = 1;
	result = db_read(db, entry);
	if (result)
	{
		success = 0;
		display_entry(result);
		free_entry(result);
	}
	return (success);
}

static void	run_command(const char *c, t_db *db, t_cmd *cmd, int *success)
{
	t_entry	*entry;

	entry = NULL;
	if (!ft_strcmp(c, "populate"))
		*success = db_populate(db);
	else if (!ft_strcmp(c, "create"))
	{
		entry = parse_entry(cmd);
		*success = db_create(db, entry);
	}
	else if (!ft_strcmp(c, "read"))
	{
		entry = parse_entry(cmd);
		*success = output_read(db, entry);
	}
	else if (!ft_strcmp(c, "update"))
		*success = db_update(db, cmd);
	else if (!ft_strcmp(c, "delete"))
	{
		entry = parse_entry(cmd);
		*success = db_delete(db, entry);
	}
	else
		ft_fprintf((*success = 2), "Invalid command: %s\n", c);
	free_entry(entry);
}

int			db_exec(t_db *db, t_cmd *cmd)
{
	int		success;

	run_command(cmd->argv[0], db, cmd, &success);
	return (success);
}
