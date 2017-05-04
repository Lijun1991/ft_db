/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   db_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: varnaud <varnaud@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/02 20:56:38 by varnaud           #+#    #+#             */
/*   Updated: 2017/05/04 01:15:20 by varnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_db.h"

int		db_exec(t_db *db, t_cmd *cmd)
{
	int		success;
	t_entry	*input;
	t_entry	*result;

	if (!strcmp(cmd->argv[0], "update"))
		success = db_update(db, cmd);
	else
	{
		input = parse_entry(cmd);
		if (input == NULL)
		{
			ft_fprintf(2, "Invalid entry.\n");
			return (1);
		}
		result = NULL;
		success = 0;
		if (!cmd || !cmd->argv[0])
			success = 1;
		if (!strcmp(cmd->argv[0], "create"))
			success = db_create(db, input);
		else if (!strcmp(cmd->argv[0], "read"))
		{
			if ((result = db_read(db, input)) == NULL)
				success = 1;
			else
				display_entry(result);
		}
		else if (!strcmp(cmd->argv[0], "delete"))
			success = db_delete(db, input);
		else if (!strcmp(cmd->argv[0], "populate"))
			success = populate(db);
		else
		{
			usage();
			success = 1;
		}
		free_entry(input);
		free_entry(result);
	}
	return (success);
}
