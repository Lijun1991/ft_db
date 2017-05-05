/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_entry.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: varnaud <varnaud@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/02 22:58:41 by varnaud           #+#    #+#             */
/*   Updated: 2017/05/05 00:13:57 by varnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_db.h"

static void	*cleanup(t_entry *entry)
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
				free(data->key);
				free(data->value);
				free(data);
				data = tmp;
			}
		}
		free(entry->id);
		free(entry);
	}
	return (NULL);
}

static int	check_dup(t_data *data, char *p, char *key)
{
	while (data)
	{
		if (ft_strncmp(data->key, key, p - key) == 0)
			return (1);
		data = data->next;
	}
	return (0);
}

static int	parse_argument(char *av, t_entry *entry, t_data ***cur)
{
	int		len;
	char	*p;

	len = ft_strlen(av);
	if (!ft_strncmp(av, "id:", 3) && !ft_strchr(&av[3], ':'))
	{
		if (!entry->id && len > 3)
			entry->id = ft_strdup(&av[3]);
		else
			return (1);
	}
	else if ((p = ft_strchr(av, ':')) && p != av
		&& !ft_strchr(p + 1, ':') && !check_dup(entry->data, p, av))
	{
		**cur = malloc(sizeof(t_data));
		(**cur)->next = NULL;
		(**cur)->key = ft_strndup(av, p - av);
		(**cur)->value = ft_strdup(p + 1);
		*cur = &(**cur)->next;
	}
	else
		return (1);
	return (0);
}

t_entry		*parse_entry(t_cmd *cmd)
{
	t_entry	*entry;
	t_data	**cur;
	int		i;

	if (!cmd || !cmd->argv[0])
		return (NULL);
	entry = malloc(sizeof(t_entry));
	ft_memset(entry, 0, sizeof(t_entry));
	cur = &entry->data;
	i = 0;
	while (cmd->argv[++i])
		if (parse_argument(cmd->argv[i], entry, &cur))
			return (cleanup(entry));
	return (entry);
}
