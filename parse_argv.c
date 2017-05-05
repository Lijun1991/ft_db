/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_argv.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: varnaud <varnaud@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/02 20:52:12 by varnaud           #+#    #+#             */
/*   Updated: 2017/05/05 01:08:12 by lwang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_db.h"

t_cmd	*parse_argv(int ac, char **av)
{
	t_cmd	*cmd;
	int		i;

	cmd = malloc(sizeof(t_cmd));
	ft_memset(cmd, 0, sizeof(t_cmd));
	cmd->argv = malloc(sizeof(char*) * ac);
	i = 0;
	while (*++av)
	{
		cmd->argv[i++] = ft_strdup(*av);
		cmd->argc++;
	}
	cmd->argv[i] = NULL;
	return (cmd);
}
