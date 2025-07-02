/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihajji <ihajji@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 14:26:40 by ihajji            #+#    #+#             */
/*   Updated: 2025/06/29 11:47:33 by zbengued         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <get_next_line.h>

static void	*ft_calloc(size_t nmemb, size_t size)
{
	char	*mem;

	mem = malloc(nmemb * size);
	if (!mem)
		return (NULL);
	while (size--)
		mem[size] = 0;
	return (mem);
}

static char	*extract_line(char **last)
{
	char	*tmp;

	tmp = dup_until(find_chr(*last, NL) + 1, 0);
	if (!tmp)
		return (clean_up((void **)last));
	clean_up((void **) last);
	*last = tmp;
	if (find_chr(tmp, NL))
		return (dup_until(*last, NL));
	return (NULL);
}

static char	*read_buffer(int fd, char **last)
{
	ssize_t	bytes;
	char	*line;
	char	*buffer;

	line = *last;
	buffer = ft_calloc((unsigned int)BUFFER_SIZE + 1, 1);
	if (!buffer)
		return (clean_up((void **)last));
	while (!find_chr(buffer, NL))
	{
		bytes = read(fd, buffer, BUFFER_SIZE);
		if (bytes == -1)
			return (clean_up((void **)&buffer), clean_up((void **)last));
		buffer[bytes] = 0;
		line = join_reads(line, buffer);
		if (!line)
			return (clean_up((void **)&buffer), clean_up((void **)last));
		if (bytes == 0)
			break ;
	}
	*last = buffer;
	if (!line[0])
		return (clean_up((void **)last), clean_up((void **)&line));
	return (line);
}

void	*clean_up(void **p)
{
	free(*p);
	*p = NULL;
	return (NULL);
}

char	*get_next_line(int fd)
{
	static char	*last;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || BUFFER_SIZE >= INT_MAX)
		return (NULL);
	line = NULL;
	if (find_chr(last, NL))
		line = extract_line(&last);
	if (line)
		return (line);
	line = read_buffer(fd, &last);
	return (line);
}
