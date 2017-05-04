/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_db.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: varnaud <varnaud@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/01 13:25:20 by varnaud           #+#    #+#             */
/*   Updated: 2017/05/03 17:41:59 by varnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_DB_H
# define FT_DB_H
# include "data.h"
# include "libft.h"
# include <sys/stat.h>
# define CREATE 1
# define READ 2
# define UPDATE 3
# define DELETE 4
# define GOTO(label) goto label


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

typedef struct		s_sample
{
	char			*id;
	char			*piscine;
	char			*name;
	char			*mobile;
	char			*email;
	char			*picture;
}					t_sample;

typedef struct		s_cmd
{
	char			**argv;
	int				argc;
}					t_cmd;

t_cmd				*parse_argv(int ac, char **av);
int					db_exec(t_db *db, t_cmd *cmd);
void				db_prompt(t_db *db);
t_entry				*get_entry(void);
void				free_cmd(t_cmd *cmd);
void				free_entry(t_entry *lst);
int					db_create(t_db *db, t_entry *entry);
int					populate(t_db *db);
t_entry				*parse_entry(t_cmd *cmd);
void				usage(void);
t_entry				*db_read(t_db *db, t_entry *entry);
void				display_entry(t_entry *entry);
int					db_delete(t_db *db, t_entry *entry);
char				*check_id_exit(t_db *db, char *id);

#endif
