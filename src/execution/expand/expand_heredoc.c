/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_herdoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbengued <zbengued@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 16:22:44 by zbengued          #+#    #+#             */
/*   Updated: 2025/06/29 18:11:36 by zbengued         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <execution.h>
#include <parsing.h>
#include <ft_string.h>

static void	extract_heredoc_content(int fd_heredoc, t_str *content)
{
	char	*line;

	line = get_next_line(fd_heredoc);
	while (line)
	{
		str_append(content, line);
		free(line);
		line = get_next_line(fd_heredoc);
	}
}

static void	expand_heredoc_content(t_str *content, t_env *env)
{
	t_str	mask;

	mask = build_mask(content);
	expand_var(content, env, &mask);
}

void	expand_heredoc(t_str *filename, t_env *env)
{
	int			fd_heredoc;
	t_str		content;

	if (str_find(filename, "EXPAND") == -1)
		return;
	fd_heredoc = open(filename->data, O_RDONLY);
	if (fd_heredoc == -1)
		return;
	extract_heredoc_content(fd_heredoc, &content);
	close(fd_heredoc);
	expand_heredoc_content(&content, env);
	fd_heredoc = open(filename->data, O_WRONLY | O_TRUNC);
	if (fd_heredoc == -1)
		return;
	ft_dprintf(fd_heredoc, "%s", content.data);
	close(fd_heredoc);
}
