/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: varnaud <varnaud@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/03 15:53:41 by varnaud           #+#    #+#             */
/*   Updated: 2017/05/03 15:54:15 by varnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_db.h"

void	display_entry(t_entry *entry)
{
	t_data	*c;

	printf("%s:\n", entry->id);
	c = entry->data;
	while (c)
	{
		if (!strcmp(c->key, "picture"))
			printf("%s: \033]1337;File=inline=1:%s:\a\n", c->key, c->value);
		else
			printf("%s: %s\n", c->key, c->value);
		c = c->next;
	}
	printf("\n");
}

void	display_entries(t_entry *lst)
{
	while (lst)
	{
		display_entry(lst);
		lst = lst->next;
	}
}
