/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: varnaud <varnaud@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/16 18:11:39 by varnaud           #+#    #+#             */
/*   Updated: 2017/04/17 21:26:19 by varnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	**ft_arrayadd(char **a, const char *env)
{
	char	**new;
	int		size;
	int		i;

	size = 0;
	if (env == NULL)
		return (NULL);
	if (a == NULL)
		return (ft_strsplit(env, '\0'));
	while (a[size])
		size++;
	new = malloc(sizeof(char*) * (size + 2));
	i = 0;
	while (i < size)
	{
		new[i] = a[i];
		i++;
	}
	new[i++] = ft_strdup(env);
	new[i] = NULL;
	return (new);
}

static char	**ft_arrayrm(char **a, const char *key)
{
	char	**new;
	int		size;
	int		i;
	int		j;

	size = 0;
	while (a[size])
		size++;
	new = malloc(sizeof(char*) * (size + 1));
	i = 0;
	j = 0;
	while (i < size)
	{
		if (ft_strcmp(a[i], key))
			new[j++] = a[i];
		i++;
	}
	new[j] = NULL;
	return (new);
}

char		**ft_findenv(char **env, const char *key)
{
	int		len;

	if (env == NULL || key == NULL)
		return (NULL);
	len = ft_strlen(key);
	while (*env)
	{
		if (!ft_strncmp(*env, key, len))
			return (env);
		env++;
	}
	return (NULL);
}

int			ft_setenv(char ***env, const char *key, const char *value)
{
	char	**variable;
	char	*newvalue;
	char	**newenv;

	if (key == NULL || value == NULL)
		return (1);
	variable = ft_findenv(*env, key);
	newvalue = ft_strcjoin(key, value, '=');
	if (variable)
	{
		free(*variable);
		*variable = newvalue;
	}
	else
	{
		newenv = ft_arrayadd(*env, newvalue);
		free(newvalue);
		free(*env);
		*env = newenv;
	}
	return (0);
}

int			ft_unsetenv(char ***env, const char *key)
{
	char	**variable;
	char	**newenv;

	if (env == NULL || key == NULL)
		return (1);
	variable = ft_findenv(*env, key);
	if (variable)
	{
		newenv = ft_arrayrm(*env, *variable);
		free(*variable);
		free(*env);
		*env = newenv;
	}
	else
		return (1);
	return (0);
}
