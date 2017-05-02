/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: varnaud <varnaud@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/21 22:18:14 by varnaud           #+#    #+#             */
/*   Updated: 2017/03/21 23:30:11 by varnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLORS_H
# define COLORS_H

# define SET_BOLD "\e[1m"
# define SET_DIM "\e[2m"
# define SET_UNDERLINED "\e[4m"
# define SET_BLINK "\e[5m"
# define SET_REVERSE "\e[7m"
# define SET_HIDDEN "\e[8m"

# define RESET_BOLD "\e[21m"
# define RESET_DIM "\e[22m"
# define RESET_UNDERLINED "\e[24m"
# define RESET_BLINK "\e[25m"
# define RESET_REVERSE "\e[27m"
# define RESET_HIDDEN "\e[28m"

# define DEFAULT "\e[39m"
# define BLACK "\e[30m"
# define RED "\e[31m"
# define GREEN "\e[32m"
# define YELLOW "\e[33m"
# define BLUE "\e[34m"
# define MAGENTA "\e[35m"
# define CYAN "\e[36m"
# define LIGHT_GRAY "\e[90m"
# define LIGHT_RED "\e[91m"
# define LIGHT_GREEN "\e[92m"
# define LIGHT_YELLOW "\e[93m"
# define LIGHT_BLUE "\e[94m"
# define LIGHT_MAGENTA "\e[95m"
# define LIGHT_CYAN "\e[96m"
# define WHITE "\e[97m"

# define BG_DEFAULT "\e[49m"
# define BG_BLACK "\e[40m"
# define BG_RED "\e[41m"
# define BG_GREEN "\e[42m"
# define BG_YELLOW "\e[43m"
# define BG_BLUE "\e[44m"
# define BG_MAGENTA "\e[45m"
# define BG_CYAN "\e[46m"
# define BG_LIGHT_GRAY "\e[47m"
# define BG_DARK_GRAY "\e[100m"
# define BG_LIGHT_RED "\e[101m"
# define BG_LIGHT_GREEN "\e[102m"
# define BG_LIGHT_YELLOW "\e[103m"
# define BG_LIGHT_BLUE "\e[104m"
# define BG_LIGHT_MAGENTA "\e[105m"
# define BG_LIGHT_CYAN "\e[106m"
# define BG_WHITE "\e[107m"

#endif
