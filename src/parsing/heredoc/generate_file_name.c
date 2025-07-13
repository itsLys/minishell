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

static void	generate_safe_random_string(char *buffer)
{
	int				fd;
	unsigned char	random_bytes[10];
	size_t			i;

	fd = open("/dev/urandom", O_RDONLY);
	i = 0;
	if (fd < 0 || read(fd, random_bytes, 10) != (ssize_t)10)
	{
		close(fd);
		while (i < 10)
			buffer[i++] = 'X';
		buffer[10] = '\0';
		return ;
	}
	close(fd);
	while (i < 10)
	{
		buffer[i] = SCH[random_bytes[i] % SAFE_CHARS_LEN];
		i++;
	}
	buffer[10] = '\0';
}

t_str	generate_file_name(void)
{
	t_str	prefix;
	t_str	filename;
	char	suffix[11];

	str_create(&filename, "/tmp/");
	str_create(&prefix, "heredoc_");
	generate_safe_random_string(suffix);
	str_append(&prefix, suffix);
	str_append(&filename, prefix.data);
	str_destroy(&prefix);
	return (filename);
}
