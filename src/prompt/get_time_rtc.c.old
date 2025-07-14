/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_time_rtc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbengued <zbengued@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 00:28:56 by zbengued          #+#    #+#             */
/*   Updated: 2025/07/08 00:49:26 by zbengued         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

// Fonction qui lit tout le contenu du fichier dans buf
// Retourne le nombre d'octets lus, ou -1 si erreur
static int	read_file(const char *path, char *buf, int buf_size)
{
	int	fd;
	int	bytes_read;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (-1);
	bytes_read = read(fd, buf, buf_size - 1);
	close(fd);
	if (bytes_read <= 0)
		return (-1);
	buf[bytes_read] = '\0';
	return (bytes_read);
}

// Cherche la position de la ligne qui commence par needle dans buf
// Retourne l'index de début ou -1 si pas trouvé
static int	find_line_start(const char *buf, const char *needle, int needle_l)
{
	int	i;

	i = 0;
	while (buf[i])
	{
		if (ft_strncmp(buf + i, needle, needle_l) == 0)
			return (i);
		while (buf[i] && buf[i] != '\n')
			i++;
		if (buf[i])
			i++;
	}
	return (-1);
}

// Copie la ligne (sans le prefix) dans out, max_len-1 max
static void	copy_line(const char *start, char *out, int max_len)
{
	int	len;
	int	i;

	len = ft_strlen_until(start, '\n');
	if (len >= max_len)
		len = max_len - 1;
	i = 0;
	while (i < len)
	{
		out[i] = start[i];
		i++;
	}
	out[i] = '\0';
}

// Nouveau parse_rtc_time utilisant les fonctions plus petites
static int	parse_rtc_time(const char *buf, char *out, int max_len)
{
	const char	*needle = "rtc_time\t: ";
	int			pos;

	pos = find_line_start(buf, needle, 11);
	if (pos == -1)
		return (-1);
	copy_line(buf + pos + 11, out, max_len);
	return (0);
}

// Fonction principale qui combine tout
int	get_rtc_time(char *out, int max_len)
{
	char	buf[512];
	int		bytes_read;

	bytes_read = read_file("/proc/driver/rtc", buf, sizeof(buf));
	if (bytes_read < 0)
		return (-1);
	return (parse_rtc_time(buf, out, max_len));
}
