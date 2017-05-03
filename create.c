/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwang <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/01 22:04:40 by lwang             #+#    #+#             */
/*   Updated: 2017/05/02 21:50:41 by varnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_db.h"

static int	write_entry_to_file(t_entry *entry, char *file)
{
	FILE  	*fptr;
	t_data	*current;

	fptr = fopen(file, "a");
	if (fptr == NULL)
	{
		perror("fopen");
		return (1);
	}
	current = entry->data;
	while (current)
	{
		fprintf(fptr, "%s:%s\n", current->key, current->value);
		current = current->next;
	}
	fclose(fptr);
	return (0);
}

int		db_create(t_db *db, t_entry *entry)
{
	char	*file;
	struct stat	buf;
	int		error;

	error = 0;
	file = ft_strcjoin(db->path, entry->id, '/');
	if (stat(file, &buf) == -1 || access(file, R_OK | W_OK))
		error = write_entry_to_file(entry, file);
	else
	{
		perror("access");
		error = 1;
	}
	free(file);
	return (error);
}

/*
int main()
{
	t_db *db;
	t_entry *entry;
	t_data *data;
	t_data *data1;

	db = (t_db*)malloc(sizeof(t_db));
	db->path = strdup("/nfs/2016/l/lwang/ft_db/db");

	entry = (t_entry*)malloc(sizeof(t_entry));
	entry->id = strdup("lwang");
	entry->next = NULL;

	// data = NULL;

	printf("data: %ld\n*data: %ld\nt_data: %ld\n", sizeof(data1), sizeof(*data1), sizeof(t_data));
	data1 = malloc(sizeof(data1));
	data1 = malloc(sizeof(t_data));
	data1->key = strdup("piscine");
	data1->value = strdup("july 2016");
	data1->next = NULL;
	entry->data = data1;

	//printf("CREATE\n");
	db_create(db, entry);
	return (0);
}
*/
