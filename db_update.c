/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   db_update.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: varnaud <varnaud@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/03 21:22:32 by varnaud           #+#    #+#             */
/*   Updated: 2017/05/04 23:11:14 by varnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_db.h"

static int		parse_cmd_file(t_entry *file, char **av)
{
	t_data	*data;
	int		i;

	i = 1;
	while (av[++i])
	{
		if (!ft_strcmp(av[i], "-d"))
		{
			if ((data = parse_data(av[++i])) == NULL)
				return (1);
			if ((remove_data(file, data)))
				return (1);
		}
		else
		{
			if ((data = parse_data(av[i])) == NULL)
				return (1);
			if ((insert_data(file, data)))
				return (1);
		}
		free_data(&data);
	}
	return (0);
}

static t_entry	*get_file(t_db *db, t_cmd *cmd)
{
	t_entry	*file;
	t_entry	e;

	file = NULL;
	if (cmd->argc > 1)
	{
		if (!ft_strncmp(cmd->argv[1], "id:", 3))
		{
			e.id = &cmd->argv[1][3];
			file = db_read(db, &e);
		}
		else
			ft_fprintf(2, "Entry invalid.\n");
	}
	else
		ft_fprintf(2, "Please specify an id.\n");
	return (file);
}

int				db_update(t_db *db, t_cmd *cmd)
{
	t_entry	*file;

	if ((file = get_file(db, cmd)) == NULL)
		return (1);
	if (parse_cmd_file(file, cmd->argv))
	{
		ft_fprintf(2, "Invalid entry.\n");
		free_entry(file);
		return (1);
	}
	db_delete(db, file);
	db_create(db, file);
	free_entry(file);
	return (0);
}
