/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sort.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: varnaud <varnaud@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/01 14:10:29 by varnaud           #+#    #+#             */
/*   Updated: 2017/02/02 17:39:46 by varnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	swap(char **s1, char **s2)
{
	char	*tmp;

	tmp = *s1;
	*s1 = *s2;
	*s2 = tmp;
}

char		**ft_sort_words(char **words, int nbwords)
{
	int		i;
	int		j;

	i = 0;
	while (i < nbwords)
	{
		j = i + 1;
		while (j < nbwords)
		{
			if (ft_strcmp(words[i], words[j]) > 0)
				swap(&words[i], &words[j]);
			j++;
		}
		i++;
	}
	return (words);
}
