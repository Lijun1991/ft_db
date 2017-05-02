/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_gnl.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: varnaud <varnaud@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/18 21:21:48 by varnaud           #+#    #+#             */
/*   Updated: 2017/04/18 21:25:33 by varnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "gnl.h"

int		free_gnl(t_fd **list)
{
	t_fd	*current;
	t_fd	*n;

	current = *list;
	while (current)
	{
		if (current->buf)
			free(current->buf);
		n = current->next;
		free(current);
		current = n;
	}
	*list = NULL;
	return (-1);
}
