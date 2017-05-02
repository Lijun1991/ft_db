/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: varnaud <varnaud@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/01 13:27:22 by varnaud           #+#    #+#             */
/*   Updated: 2017/05/01 23:11:44 by varnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DATA_H
# define DATA_H
# include "ft_db.h"

typedef struct		s_data
{
	char			*key;
	char			*value;
	struct s_data	*next;
}					t_data;

typedef struct		s_entry
{
	int			id;
	t_data		**data;
};

#endif
