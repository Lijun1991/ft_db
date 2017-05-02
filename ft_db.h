/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_db.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: varnaud <varnaud@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/01 13:25:20 by varnaud           #+#    #+#             */
/*   Updated: 2017/05/01 22:51:05 by varnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_DB_H
# define FT_DB_H
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <fcntl.h>
# include "data.h"
# include "libft.h"
# define CREATE 1
# define READ 2
# define UPDATE 3
# define DELETE 4


typedef struct		s_db
{
	char			*path;
}					t_db;

typedef struct		s_crud
{
	int				type;
	t_entry			*entry;
}					t_crud;

typedef struct		s_uid
{
	char			*uid;
	struct s_uid	*next;
}					t_uid;

t_crud				*parse_argv(char **argv);
int					do_operation(t_crud *o);

#endif
