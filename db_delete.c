/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   db_delete.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwang <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/03 15:22:02 by lwang             #+#    #+#             */
/*   Updated: 2017/05/03 15:22:05 by lwang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_db.h"

int		db_delete(t_db *db, t_entry *entry)
{
	struct stat sb;
	char		*file;
	int			ret;

	if (!entry->id)
	{
		perror("id no exist");
		return (1);
	}
	file = ft_strcjoin(db->path, entry->id, '/');
	if (stat(file, &sb) == -1)
	{
		free(file);
		perror("id no exist");
		return (1);
	}
	ret = remove(file);
	free(file);
	if (ret)
		perror("remove");
	return (ret);
}

int		main(int ac, char **av)
{
	t_db	db;
	t_entry	entry;

	db.path = ft_strdup("/nfs/2016/l/lwang/ft_db/db");
	entry.id = ft_strdup(av[1]);
	db_delete(&db, &entry);
	free(entry.id);
	free(db.path);
	return (0);
}
