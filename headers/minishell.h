/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbengued <zbengued@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 22:30:19 by zbengued          #+#    #+#             */
/*   Updated: 2025/06/10 16:42:45 by ihajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stddef.h>
# include <sys/types.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <limits.h>
# include <string.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <libft.h>



typedef struct s_env
{
	char	*name;
	char	*value;
	bool	is_exported;
	struct s_env *next;
}	t_env ;

// test
void	print_env(t_env *env);

typedef struct t_builtin
{
	char	*name;
	int		(*function)(char **);
} t_builtin ;

typedef struct s_data
{
	t_env		*env_copy;
	char		*input;
	int			status;
	char		*lwd;
	char		*cwd;
	t_builtin	*builtins; // consider throwing this, since it is only used once
}	t_data;

t_data *g_data(void);
int init_minishell(char **env);

void *free_env_copy(t_env *env_copy);
#endif // !MINISHELL_H
