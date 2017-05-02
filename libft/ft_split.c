/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: varnaud <varnaud@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/22 21:41:44 by varnaud           #+#    #+#             */
/*   Updated: 2017/04/22 22:51:50 by varnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	**cleanup(char **a, int size)
{
	while (size--)
		free(a[size]);
	free(a);
	return (NULL);
}

static int	setup_line(char *line, int i, int count)
{
	while (line[i] && BLANK(line[i]))
		line[i++] = '\0';
	if (line[i])
	{
		count++;
		while (line[i] && !BLANK(line[i]))
			i++;
	}
	else
		return (count);
	return (setup_line(line, i, count));
}

char		**ft_split(char *line, int len, int *words)
{
	char	**argv;
	int		i;
	int		j;
	int		count;

	if (line == NULL || len < 0)
		return (NULL);
	count = setup_line(line, 0, 0);
	if (!(argv = malloc(sizeof(char*) * (count + 1))))
		return (NULL);
	i = 0;
	j = 0;
	while (j < count)
	{
		while (i < len && line[i] == '\0')
			i++;
		if (!(argv[j] = ft_strdup(&line[i])))
			return (cleanup(argv, j));
		while (i < len && line[i] != '\0')
			i++;
		j++;
	}
	if (!(argv[count] = NULL) && words)
		*words = count;
	return (argv);
}
