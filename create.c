/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwang <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/01 22:04:40 by lwang             #+#    #+#             */
/*   Updated: 2017/05/04 15:27:15 by varnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_db.h"

static int	write_entry_to_file(t_entry *entry, char *file)
{
	FILE  	*fptr;
	t_data	*current;

	fptr = fopen(file, "w");
	if (fptr == NULL)
	{
		perror("fopen");
		return (1);
	}
	current = entry->data;
	while (current)
	{
		fprintf(fptr, "%s:%s\n", current->key, current->value == NULL ? "" : current->value);
		current = current->next;
	}
	fclose(fptr);
	return (0);
}

int		db_create(t_db *db, t_cmd *cmd)
{
	char	*file;
	struct stat	buf;
	int		error;
	t_entry	*entry;

	if ((entry = parse_entry(cmd)) == NULL)
	{
		ft_fprintf(2, "Entry invalid.\n");
		return (1);
	}
	error = 0;
	file = ft_strcjoin(db->path, entry->id, '/');
	if (stat(file, &buf) == -1)
		error = write_entry_to_file(entry, file);
	else
	{
		ft_fprintf(2, "id: %s already exist in database.\n", entry->id);
		error = 1;
	}
	free(file);
	free_entry(entry);
	return (error);
}
