/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reading_stdin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbengued <zbengued@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 20:54:02 by zbengued          #+#    #+#             */
/*   Updated: 2025/06/25 21:18:28 by zbengued         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_string.h>
#include <parsing.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <fcntl.h>

t_str	generate_file_name(void)
{
	ssize_t	n;
	t_str	prefix;
	t_str	suffix;
	char	buff[16];
	int		fd_random;

	fd_random = open("/dev/random", O_RDONLY);
	str_create(&prefix, "heredoc");
	

}
// int main (int ac, char **av)
// {
// 	run_heredoc(av[1]);
// }
