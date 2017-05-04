/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   db_update.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: varnaud <varnaud@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/03 21:22:32 by varnaud           #+#    #+#             */
/*   Updated: 2017/05/04 01:25:29 by varnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_db.h"

static int		cleanup(t_cmd *a, t_cmd *b)
{
	if (a)
		free_cmd(a);
	if (b)
		free_cmd(b);
	return (1);
}

static void		add_arg(t_cmd **c, int ac, const char *arg)
{
	if (*c == NULL)
	{
		*c = malloc(sizeof(t_cmd));
		memset(*c, 0, sizeof(t_cmd));
		(*c)->argv = malloc(sizeof(char*) * ac);
		(*c)->argv[0] = strdup("update");
		(*c)->argc++;
		(*c)->argv[1] = NULL;
	}
	(*c)->argv[(*c)->argc] = strdup(arg);
	(*c)->argc++;
	(*c)->argv[(*c)->argc] = NULL;
}

static t_entry	*update_entry(t_entry *file, t_entry *update, t_entry *delete)
{
	t_entry	*entry;
	t_data	*df;
	t_data	*du;
	t_data	*dd;
	t_data	**cur;
	int		nope;

	entry = malloc(sizeof(t_entry));
	memset(entry, 0, sizeof(t_entry));
	entry->id = strdup(file->id);
	cur = &entry->data;
	df = file->data;
	du = update->data;
	if (delete)
		dd = delete->data;
	thisisfine:
	while (df)
	{
		if (delete)
		{
			dd = delete->data;
			while (dd)
			{
				if (strcmp(df->key, dd->key) == 0)
				{
					df = df->next;
					GOTO(thisisfine);
				}
				dd = dd->next;
			}
		}
		if ((du = update->data))
			while (du)
			{
				if (strcmp(df->key, du->key) == 0)
				{
					add_data(du->key, du->value, &cur);
					break ;
				}
				du = du->next;
			}
		if (!du)
			add_data(df->key, df->value, &cur);
		df = df->next;
	}
	du = update->data;
	while (du)
	{
		nope = 0;
		df = entry->data;
		while (df)
		{
			if (strcmp(df->key, du->key) == 0)
				nope = 1;
			df = df->next;
		}
		if (!nope)
			add_data(du->key, du->value, &cur);
		du = du->next;
	}
	return (entry);
}

int				db_update(t_db *db, t_cmd *cmd)
{
	t_entry	*entry;
	t_cmd	*update;
	t_cmd	*delete;
	int		i;
	int		err;
	t_entry	*up;
	t_entry	*file;
	t_entry	*del;

	err = 0;
	update = NULL;
	delete = NULL;
	up = NULL;
	file = NULL;
	del = NULL;
	entry = NULL;
	i = 0;
	while (cmd->argv[++i])
		if (cmd->argv[i][0] == '-')
		{
			if (cmd->argv[i][1] == 'd' && cmd->argv[i][2] == '\0')
			{
				if (!cmd->argv[i + 1])
				{
					err = 1;
					GOTO(quit);
				}
				add_arg(&delete, cmd->argc + 1, cmd->argv[i + 1]);
				i++;
			}
		}
		else
			add_arg(&update, cmd->argc + 1, cmd->argv[i]);
	if (!(up = parse_entry(update)) && (err = 1))
		GOTO(quit);
	if (delete && !(del = parse_entry(delete)) && (err = 1))
		GOTO(quit);
	if (!(file = db_read(db, up)) && (err = 1))
		GOTO(quit);
	entry = update_entry(file, up, del);
	db_delete(db, file);
	db_create(db, entry);
	quit:
	cleanup(update, delete);
	free_entry(up);
	free_entry(del);
	free_entry(file);
	free_entry(entry);
	return (err);
}
