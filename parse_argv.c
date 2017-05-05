/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_argv.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: varnaud <varnaud@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/02 20:52:12 by varnaud           #+#    #+#             */
/*   Updated: 2017/05/05 15:50:01 by varnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_db.h"

static int	validate_arg(int ac, char **av)
{
	int		i;
	int		total;

	if (ac > MAX_ARGC)
		return (1);
	total = 1;
	i = 0;
	while (av[++i])
	{
		total += ft_strlen(av[i]);
		if (total <= 0)
			return (1);
	}
	return (total > MAX_ENTRY_SIZE);
}

int			get_file_size(const char *path)
{
	struct stat	s;

	if (stat(path, &s) == -1)
	{
		printf("File %s does not exist.\n", path);
		return (-1);
	}
	else
		return (s.st_size);
}

t_cmd		*parse_argv(int ac, char **av)
{
	t_cmd	*cmd;
	int		i;

	if (validate_arg(ac, av))
	{
		ft_fprintf(2, "Argument limits violated.\n");
		return (NULL);
	}
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
