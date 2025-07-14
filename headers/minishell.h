/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihajji <ihajji@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 14:51:47 by ihajji            #+#    #+#             */
/*   Updated: 2025/07/14 14:51:54 by ihajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <libft.h>
# include <get_next_line.h>
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stddef.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/types.h>
# include <unistd.h>
# include <sys/wait.h>
# include <dirent.h>
# include <sys/types.h>
# include <ft_string.h>
# include <dirent.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <signals.h>
# include <linux/limits.h>

int		get_rtc_time(char *out, int max_len);

// prompt engineering
char	*get_time(void);
char	*get_branch(void);
char	*get_status_color(void);
void	build_first_line(char *prompt, char *status, char *user, char *time);
void	build_second_line(char *prompt, char *pwd, char *branch);

// test
#endif // !MINISHELL_H
