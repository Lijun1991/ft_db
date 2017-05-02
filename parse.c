/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: varnaud <varnaud@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/01 13:33:58 by varnaud           #+#    #+#             */
/*   Updated: 2017/05/01 17:11:24 by varnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_db.h"

t_crud	*parse_argv(char **argv)
{
	t_crud	*o;
	int		i;
	char	*p;

	o = malloc(sizeof(t_crud));
	i = 0;
	while (argv[++i])
	{
		if (i == 1)
		{
			if (strcmp(argv[i], "create"))
				o->type = CREATE;
			else if (strcmp(argv[i], "read"))
				o->type = READ;
			else if (strcmp(argv[i], "update"))
				o->type = UPDATE;
			else if (strcmp(argv[i], "delete"))
				o->type = DELETE;
			else
				return (NULL);
		}
		else
		{
			if ((p = strchr(argv[i], '=')) == NULL)
				return (NULL);
			o->key = strndup(argv[i], p - argv[i]);
			o->value = strdup(p + 1);
		}
	}
	return (o);
}
