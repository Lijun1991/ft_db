/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: varnaud <varnaud@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/03 15:37:51 by varnaud           #+#    #+#             */
/*   Updated: 2017/05/03 15:58:03 by varnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_db.h"

void	free_cmd(t_cmd *cmd)
{
	int		i;

	if (cmd)
	{
		i = 0;
		if (cmd->argv)
		{
			while (cmd->argv[i])
				free(cmd->argv[i++]);
			free(cmd->argv);
		}
		free(cmd);
	}
}

void	free_entry(t_entry *lst)
{
	t_entry	*tmp;
	t_data	*td;

	if (lst)
		while (lst)
		{
			tmp = lst->next;
			if (lst->id)
				free(lst->id);
			while (lst->data)
			{
				td = lst->data->next;
				if (lst->data->key)
					free(lst->data->key);
				if (lst->data->value)
					free(lst->data->value);
				free(lst->data);
				lst->data = td;
			}
			free(lst);
			lst = tmp;
		}
}
