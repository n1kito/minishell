/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_fd.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjallada <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 11:08:55 by mjallada          #+#    #+#             */
/*   Updated: 2022/05/04 11:08:57 by mjallada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_FD_H
# define FT_PRINTF_FD_H

# include <stdarg.h>

# if defined (__APPLE__)
#  define PTR_NULL "0x0"
# elif __linux__
#  define PTR_NULL "(nil)"
# endif

int				ft_parameter_gps(int fd, char format, va_list args);
int				ft_puthexa_fd(int fd, unsigned long int nbr, char format);
int				ft_printf_fd(int fd, const char *str, ...);

#endif
