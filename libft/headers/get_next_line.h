/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihajji <ihajji@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 10:45:10 by ihajji            #+#    #+#             */
/*   Updated: 2024/12/09 16:49:47 by ihajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# define MAX_FD 1024
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 100000
# endif // !BUFFER_SIZE

# define NL '\n'
# include <limits.h>
# include <stdlib.h>
# include <unistd.h>

char	*get_next_line(int fd);
char	*find_chr(const char *s, int c);
char	*join_reads(char const *s1, char const *s2);
char	*dup_until(const char *s, char c);
void	*clean_up(void **p);

#endif // !GET_NEXT_LINE_H
