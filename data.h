/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: varnaud <varnaud@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/01 13:27:22 by varnaud           #+#    #+#             */
/*   Updated: 2017/05/01 17:11:38 by varnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DATA_H
# define DATA_H
# include "ft_db.h"

typedef struct	s_data
{
	void		*data;
	size_t		size;
}				t_data;

typedef struct	s_entry
{
	int			id;
	t_data		*data;
}

#endif
