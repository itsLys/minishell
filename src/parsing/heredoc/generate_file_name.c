/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generate_file_name.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbengued <zbengued@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 12:18:35 by zbengued          #+#    #+#             */
/*   Updated: 2025/07/01 12:28:00 by zbengued         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parsing.h>
#include <execution.h>

t_str	generate_file_name(void)
{
	t_str	prefix;
	t_str	suffix;
	char	buff[10];
	t_str	filename;
	int		fd_random;

	str_create(&filename, "/tmp/");
	fd_random = open("/dev/random", O_RDONLY);
	str_create(&prefix, "heredoc_");
	read(fd_random, buff, 9);
	buff[9] = '\0';
	close(fd_random);
	str_create(&suffix, buff);
	str_replace_char(&suffix, '\\', '6');
	str_append(&prefix, suffix.data);
	str_append(&filename, prefix.data);
	return (filename);
}
