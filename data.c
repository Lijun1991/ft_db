/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: varnaud <varnaud@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/04 22:36:10 by varnaud           #+#    #+#             */
/*   Updated: 2017/05/04 23:53:33 by varnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_db.h"

void	free_data(t_data **data)
{
	if (data)
	{
		if (*data)
		{
			if ((*data)->key)
				free((*data)->key);
			if ((*data)->value)
				free((*data)->value);
			free(*data);
			*data = NULL;
		}
	}
}

t_data	*add_data(const char *key, const char *value, t_data ***cur)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	memset(data, 0, sizeof(t_data));
	data->key = strdup(key);
	if (value && value[0])
		data->value = strdup(value);
	if (cur)
	{
		**cur = data;
		*cur = &(**cur)->next;
	}
	return (data);
}

t_data	*parse_data(const char *s)
{
	char	*p;
	t_data	*data;

	if (!(p = ft_strchr(s, ':')) || p == s || ft_strchr(p + 1, ':'))
		return (NULL);
	data = malloc(sizeof(t_data));
	data->key = ft_strndup(s, p - s);
	data->value = ft_strdup(p + 1);
	data->next = NULL;
	return (data);
}

int		insert_data(t_entry *entry, t_data *data)
{
	t_data	**cur;

	if (entry == NULL || data == NULL)
		return (1);
	cur = &entry->data;
	while (*cur)
	{
		if (!ft_strcmp((*cur)->key, data->key))
		{
			if ((*cur)->value)
				free((*cur)->value);
			(*cur)->value = ft_strdup(data->value);
			return (0);
		}
		cur = &(*cur)->next;
	}
	*cur = malloc(sizeof(t_data));
	(*cur)->next = NULL;
	(*cur)->key = ft_strdup(data->key);
	(*cur)->value = ft_strdup(data->value);
	return (0);
}

int		remove_data(t_entry *entry, t_data *data)
{
	t_data	*old;
	t_data	*cur;

	if (entry == NULL || data == NULL)
		return (1);
	cur = data;
	old = cur;
	while (cur)
	{
		if (!ft_strcmp(cur->key, data->key))
		{
			old->next = cur->next;
			free_data(&cur);
			return (0);
		}
		old = cur;
		cur = cur->next;
	}
	return (1);
}
