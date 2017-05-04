/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   db_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: varnaud <varnaud@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/02 20:56:38 by varnaud           #+#    #+#             */
/*   Updated: 2017/05/04 15:41:30 by varnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_db.h"

int			db_exec(t_db *db, t_cmd *cmd)
{
	char	*c;
	int		success;

	c = cmd->argv[0];
	success = 0;
	if (!ft_strcmp(c, "populate"))
		success = db_populate(db);
	else if (!ft_strcmp(c, "create"))
		success = db_create(db, cmd);
	else if (!ft_strcmp(c, "read"))
		success = db_read(db, cmd); 
	else if (!ft_strcmp(c, "update"))
		success = db_update(db, cmd);
	else if (!ft_strcmp(c, "delete"))
		success = db_delete(db, cmd);
	else
	{
		success = 1;
		ft_fprintf(2, "Invalid command: %s\n", c);
	}
	return (success);
}
