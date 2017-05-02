/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwang <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/01 22:04:40 by lwang             #+#    #+#             */
/*   Updated: 2017/05/01 23:45:49 by lwang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_db.h"

void	write_entry_to_file(t_entry *entry, char *file)
{
	FILE  	*fptr;
	t_data	*current;

	fptr = fopen(file, "a");
	if (fptr == NULL)
	{
		printf("error");
		exit(1);
	}
	fprintf(fptr, "id:%s\n", entry->id);
	current = entry->data;
	while (current)
	{
		fprintf(fptr, "%s:%s\n", current->key, current->value);
		current = current->next;
	}
	fclose(fptr);
}

int		db_create(t_db *db, t_entry *entry)
{
	char	*file;
	char	*tmp;
	struct stat	buf;

	tmp = ft_strjoin(db->path, "/");
	file = ft_strjoin(tmp, entry->id);
	free(tmp);
	//TODO if file exist, return error, else create it and write entry to it
	if (stat(file, &buf) == -1)
		write_entry_to_file(entry, file);
	else
	{
		free(file);
		printf("id exit");
		return (1);
	}
	free(file);
	return (0);
}


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


