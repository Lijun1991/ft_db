/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: varnaud <varnaud@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/01 13:17:17 by varnaud           #+#    #+#             */
/*   Updated: 2017/05/01 17:11:40 by varnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_db.h"

static void	usage(char **argv)
{
	printf("usage: %s [create | read | update | delete] [key=value]\n", argv[0]);
	exit(1);
}

int			main(int argc, char **argv)
{
	if (argc > 1)
	{
		if (parse_argv(argv))
			usage();
		do_operation();
	}
	else
		init_db();
}
