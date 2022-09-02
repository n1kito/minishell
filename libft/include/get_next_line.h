/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjallada <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 11:11:06 by mjallada          #+#    #+#             */
/*   Updated: 2022/05/12 11:11:11 by mjallada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>

# include <sys/types.h>
# include <sys/uio.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

typedef struct s_gnl
{
	char			*content;
	struct s_gnl	*next;
}				t_gnl;

char	*get_next_line(int fd);
int		found_newline(t_gnl *stash);
t_gnl	*ft_lst_get_last(t_gnl *stash);
void	read_and_stash(int fd, t_gnl **stash);
void	add_to_stash(t_gnl **stash, char *buf, int readed);
void	extract_line(t_gnl *stash, char **line);
void	generate_line(char **line, t_gnl *stash);
void	clean_stash(t_gnl **stash);
void	free_stash(t_gnl *stash);

#endif
