/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   db_delete.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwang <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/03 15:22:02 by lwang             #+#    #+#             */
/*   Updated: 2017/05/04 15:36:10 by varnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_db.h"

int		db_delete(t_db *db, t_cmd *cmd)
{
	struct stat sb;
	char		*file;
	int			ret;
	t_entry		*entry;

	if (!(entry = parse_entry(cmd)) || !entry->id)
	{
		ft_fprintf(2, "Invalid entry.\n");
		return (1);
	}
	file = ft_strcjoin(db->path, entry->id, '/');
	if (stat(file, &sb) == -1)
	{
		ft_fprintf(2, "Entry id:%s does not exist.\n", entry->id);
		free(file);
		free_entry(entry);
		return (1);
	}
	ret = remove(file);
	free(file);
	if (ret)
		perror("remove");
	free_entry(entry);
	return (ret);
}
