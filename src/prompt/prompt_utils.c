/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihajji <ihajji@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 10:10:31 by ihajji            #+#    #+#             */
/*   Updated: 2025/07/14 18:57:31 by ihajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

char	*get_status_color(void)
{
	if (g_interrupted[2] == 0)
		return (COLOR_GREEN);
	return (COLOR_RED);
}

char	*get_branch(void)
{
	char	*branch;

	branch = ft_getoutput((char *[]){"git",
			"rev-parse",
			"--abbrev-ref",
			"HEAD",
			NULL}, __environ);
	if (branch == NULL)
		return (ft_strdup("~"));
	return (branch);
}

char	*get_time(void)
{
	char	*time;

	time = ft_getoutput((char *[]){"date", "+%a %d %H:%M", NULL}, __environ);
	if (time == NULL)
		return (ft_strdup("-"));
	return (time);
}

void	build_first_line(char *prompt, char *status, char *user, char *time)
{
	ft_strlcat(prompt, "┏[", PATH_MAX);
	ft_strlcat(prompt, get_status_color(), PATH_MAX);
	ft_strlcat(prompt, status, PATH_MAX);
	ft_strlcat(prompt, COLOR_RESET, PATH_MAX);
	ft_strlcat(prompt, "]", PATH_MAX);
	ft_strlcat(prompt, "-(", PATH_MAX);
	ft_strlcat(prompt, COLOR_BLUE, PATH_MAX);
	ft_strlcat(prompt, user, PATH_MAX);
	ft_strlcat(prompt, COLOR_RESET, PATH_MAX);
	ft_strlcat(prompt, ")", PATH_MAX);
	ft_strlcat(prompt, "-(", PATH_MAX);
	ft_strlcat(prompt, COLOR_RED, PATH_MAX);
	ft_strlcat(prompt, time, PATH_MAX);
	ft_strlcat(prompt, COLOR_RESET, PATH_MAX);
	ft_strlcat(prompt, ")\n", PATH_MAX);
}

void	build_second_line(char *prompt, char *pwd, char *branch)
{
	ft_strlcat(prompt, COLOR_CYAN, PATH_MAX);
	ft_strlcat(prompt, pwd, PATH_MAX);
	ft_strlcat(prompt, COLOR_RESET, PATH_MAX);
	ft_strlcat(prompt, ")", PATH_MAX);
	ft_strlcat(prompt, "-(", PATH_MAX);
	ft_strlcat(prompt, COLOR_MAGENTA, PATH_MAX);
	ft_strlcat(prompt, branch, PATH_MAX);
	ft_strlcat(prompt, COLOR_RESET, PATH_MAX);
	ft_strlcat(prompt, ")-> ", PATH_MAX);
}
