/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: varnaud <varnaud@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/01 14:19:46 by varnaud           #+#    #+#             */
/*   Updated: 2017/04/03 21:54:48 by varnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# define LARGEST(a, b) (a > b ? a : b)
# define SMALLEST(a, b) (a < b ? a : b)
# include <stdarg.h>
# include <wchar.h>
# define F_HASH 1
# define F_ZERO 2
# define F_MINUS 4
# define F_PLUS 8
# define F_SPACE 16
# define F_WIDTH 32
# define F_PRECISION 64
# define F_HH 128
# define F_H 256
# define F_L 512
# define F_LL 1024
# define F_J 2048
# define F_Z 4096

typedef struct	s_flags
{
	char		conversion;
	int			width;
	int			precision;
	int			f;
	int			fd;
}				t_flags;

int				handle_string(t_flags *flags, char *s);
int				handle_wcstr(t_flags *flags, wchar_t *wcstr);
int				handle_signed_number(long long n, t_flags *f);
int				handle_unsigned_number(unsigned long long n, int b, t_flags *f);
int				print_arg(int fd, char **format, va_list *args);
int				do_conversion(t_flags *flags, va_list *args);
int				s_conversion(t_flags *flags, va_list *args);
int				ls_conversion(t_flags *flags, va_list *args);
int				p_conversion(t_flags *flags, va_list *args);
int				d_conversion(t_flags *flags, va_list *args);
int				ld_conversion(t_flags *flags, va_list *args);
int				i_conversion(t_flags *flags, va_list *args);
int				o_conversion(t_flags *flags, va_list *args);
int				lo_conversion(t_flags *flags, va_list *args);
int				u_conversion(t_flags *flags, va_list *args);
int				lu_conversion(t_flags *flags, va_list *args);
int				x_conversion(t_flags *flags, va_list *args);
int				cx_conversion(t_flags *flags, va_list *args);
int				c_conversion(t_flags *flags, va_list *args);
int				lc_conversion(t_flags *flags, va_list *args);
int				b_conversion(t_flags *flags, va_list *args);
int				f_conversion(t_flags *flags, va_list *args);
char			*get_float(double d);
int				error_conversion(t_flags *flags);

#endif
