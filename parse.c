/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: varnaud <varnaud@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/30 16:05:36 by varnaud           #+#    #+#             */
/*   Updated: 2017/04/18 15:10:52 by varnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	setup_line(char *line, int i, int count)
{
	while (line[i] && IS_WHITE(line[i]))
		line[i++] = '\0';
	if (line[i])
	{
		count++;
		while (line[i] && !IS_WHITE(line[i]))
		{
			if (line[i] == '"' && P_V(line, i) != '\\')
				while (line[++i])
					if (line[i] == '"' && P_V(line, i) != '\\')
						break ;
			i++;
		}
	}
	else
		return (count);
	return (setup_line(line, i, count));
}

static int	setup_argv(char **argv, int *k, int size, t_msh *msh)
{
	char	*h;
	int		len;

	len = 0;
	if (msh->line[*k] == '~')
	{
		len = ft_strlen(msh->home);
		h = malloc(sizeof(char) * (size + len));
		h = ft_strcpy(h, msh->home);
		*k += 1;
		*argv = h;
	}
	else
		*argv = malloc(sizeof(char) * size);
	return (len);
}

static char	**split_line(char *line, int size, int count, t_msh *msh)
{
	char	**argv;
	int		i;
	int		j;
	int		k;
	int		l;

	if (!(argv = malloc(sizeof(char*) * (count + 1))))
		return (NULL);
	argv[count] = NULL;
	i = 0;
	j = 0;
	while (count--)
	{
		while (i < size && line[i] == '\0')
			i++;
		k = i;
		while (i < size && line[i] != '\0')
			i++;
		l = setup_argv(&argv[j], &k, i - k + 1, msh);
		while ((argv[j][l] = line[k++]))
			l += (line[k] == '"' && line[k - 1] == '\\') || (line[k - 1] == '"'
					&& P_V(line, k - 1) != '\\') ? 0 : 1;
		j++;
	}
	return (argv);
}

t_cmd		*setup_command(char *line, t_msh *msh)
{
	t_cmd	*cmd;
	char	**argv;
	int		argc;
	int		len;

	len = ft_strlen(line);
	argc = setup_line(line, 0, 0);
	if (argc == 0)
		return (NULL);
	argv = split_line(line, len, argc, msh);
	if (argv == NULL)
		return (NULL);
	if (!(cmd = malloc(sizeof(t_cmd))))
		return (NULL);
	cmd->argv = argv;
	cmd->argc = argc;
	cmd->path = NULL;
	cmd->env = NULL;
	return (cmd);
}
