/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_entry.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: varnaud <varnaud@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/02 22:58:41 by varnaud           #+#    #+#             */
/*   Updated: 2017/05/03 00:49:24 by varnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_db.h"

static void	cleanup(t_entry *entry)
{
	t_data	*data;
	t_data	*tmp;

	if (entry)
	{
		if (entry->data)
		{
			data = entry->data;
			while (data)
			{
				tmp = data->next;
				if (data->key)
					free(data->key);
				if (data->value)
					free(data->value);
				free(data);
				data = tmp;
			}
		}
		if (entry->id)
			free(entry->id);
		free(entry);
	}
}

static int	check_dup(t_data *data, char *p, char *key)
{
	while (data)
	{
		if (strncmp(data->key, key, p - key) == 0)
			return (1);
		data = data->next;
	}
	return (0);
}

t_entry		*parse_entry(t_cmd *cmd)
{
	t_entry	*entry;
	t_data	**cur;
	int		i;
	int		len;
	char	*p;

	if (!cmd || !cmd->argv[0])
		return (NULL);
	entry = malloc(sizeof(t_entry));
	memset(entry, 0, sizeof(t_entry));
	cur = &entry->data;
	i = 0;
	while (cmd->argv[++i])
	{
		len = strlen(cmd->argv[i]);
		if (!strncmp(cmd->argv[i], "id:", 3) && !strchr(&cmd->argv[i][3], ':'))
		{
			if (!entry->id && len > 3)
				entry->id = strdup(&cmd->argv[i][3]);
			else
				GOTO(err);
		}
		else if ((p = strchr(cmd->argv[i], ':')) && p != cmd->argv[i]
			&& !strchr(p + 1, ':') && !check_dup(entry->data, p, cmd->argv[i]))
		{
			*cur = malloc(sizeof(t_data));
			(*cur)->next = NULL;
			(*cur)->key = strndup(cmd->argv[i], p - cmd->argv[i]);
			(*cur)->value = strdup(p + 1);
			cur = &(*cur)->next;
		}
		else
			GOTO(err);
	}
	return (entry);
	err:
	cleanup(entry);
	return (NULL);
}
