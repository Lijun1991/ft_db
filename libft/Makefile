# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: varnaud <varnaud@student.42.us.org>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/04/11 17:57:00 by varnaud           #+#    #+#              #
#    Updated: 2017/05/04 23:02:37 by varnaud          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	libft.a
FTSRC	=	ft_abs.c \
			ft_atoi.c \
			ft_atoi_base.c \
			ft_bzero.c \
			ft_ctoi.c \
			ft_isalnum.c \
			ft_isalpha.c \
			ft_isascii.c \
			ft_isdigit.c \
			ft_isprint.c \
			ft_iswhitespace.c \
			ft_itoa.c \
			ft_itoa_base.c \
			ft_lstadd.c \
			ft_lstdel.c \
			ft_lstdelone.c \
			ft_lstiter.c \
			ft_lstmap.c \
			ft_lstnew.c \
			ft_memalloc.c \
			ft_memccpy.c \
			ft_memchr.c \
			ft_memcmp.c \
			ft_memcpy.c \
			ft_memdel.c \
			ft_memmove.c \
			ft_memset.c \
			ft_pow.c \
			ft_putchar.c \
			ft_putchar_fd.c \
			ft_putendl.c \
			ft_putendl_fd.c \
			ft_putnbr.c \
			ft_putnbr_fd.c \
			ft_putstr.c \
			ft_putstr_fd.c \
			ft_stradd.c \
			ft_strcat.c \
			ft_strchr.c \
			ft_strclr.c \
			ft_strcmp.c \
			ft_strcpy.c \
			ft_strdel.c \
			ft_strdup.c \
			ft_strequ.c \
			ft_striter.c \
			ft_striteri.c \
			ft_strjoin.c \
			ft_strlcat.c \
			ft_strlen.c \
			ft_strmap.c \
			ft_strmapi.c \
			ft_strncat.c \
			ft_strncmp.c \
			ft_strncpy.c \
			ft_strnequ.c \
			ft_strnew.c \
			ft_strnstr.c \
			ft_strrchr.c \
			ft_strrev.c \
			ft_strsplit.c \
			ft_strstr.c \
			ft_strsub.c \
			ft_strtrim.c \
			ft_tolower.c \
			ft_toupper.c \
			ft_squareplusplus.c \
			ft_strnadd.c \
			ft_lstget.c \
			ft_memadd.c \
			ft_itoc.c \
			ft_putnbr_base.c \
			ft_putnstr.c \
			ft_numlen.c \
			ft_putcnbr_base.c \
			ft_count_words.c \
			ft_itocc.c \
			ft_strichr.c \
			ft_snumlen.c \
			ft_unumlen_base.c \
			ft_putnchar.c \
			ft_putdigit.c \
			ft_putudigit_base.c \
			ft_wctomb.c \
			ft_revbits.c \
			ft_sort.c \
			ft_dump.c \
			ft_memdup.c \
			ft_putdigit_fd.c \
			ft_putudigit_base_fd.c \
			ft_putnchar_fd.c \
			ft_putnstr_fd.c \
			gnl.c \
			free_gnl.c \
			ft_env.c \
			ft_strsubs.c \
			ft_strcjoin.c \
			ft_split.c \
			ft_strndup.c
PFDIR	=	ft_printf/
PFSRC	=	ft_printf.c \
			handle_string.c \
			handle_wcstr.c \
			handle_snumber.c \
			handle_unumber.c \
			print_arg.c \
			do_conversion.c \
			s_conversion.c \
			ls_conversion.c \
			p_conversion.c \
			d_conversion.c \
			ld_conversion.c \
			i_conversion.c \
			o_conversion.c \
			lo_conversion.c \
			u_conversion.c \
			lu_conversion.c \
			x_conversion.c \
			cx_conversion.c \
			c_conversion.c \
			lc_conversion.c \
			b_conversion.c \
			f_conversion.c \
			bignum.c \
			floating_point.c \
			mtp.c \
			error_conversion.c
SRC = $(FTSRC) $(addprefix $(PFDIR), $(PFSRC))
OBJ = $(SRC:.c=.o)
CC = gcc
CFLAGS = -Wall -Werror -Wextra -I. -I$(PFDIR)

.PHONY: clean fclean all re

all: $(NAME)

$(NAME): $(OBJ)
	ar rc $@ $^
	ranlib $@

$(OBJ): libft.h

clean:
	-@rm -f $(OBJ)

fclean: clean
	-@rm -f $(NAME)

re: fclean all
