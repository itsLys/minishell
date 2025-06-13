/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihajji <ihajji@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 20:21:39 by ihajji            #+#    #+#             */
/*   Updated: 2025/06/13 16:06:20 by ihajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef	 EXECUTION_H
# define EXECUTION_H

# include "minishell.h"
# include "parsing.h"

typedef struct s_env
{
	char			*name;
	char			*value;
	bool			exported;
	struct s_env	*next;
}	t_env ;

typedef struct t_builtin
{
	char	*name;
	int		(*function)(char **argv, t_env **env);
} t_builtin ;

typedef struct s_data
{
	t_env		*env;
	char		*input;
	int			status;
	char		*oldpwd;
	char		*pwd;
	t_builtin	*builtins; // consider throwing this, since it is only used once
}	t_data;

//testing function
void		print_env(t_env *env);

t_data		*g_data(void);

void		*free_env_copy(t_env *env_copy);

// builtins
int			echo(char **argv, t_env **env);
int			cd(char **argv, t_env **env);
int			pwd(char **argv, t_env **env);
int			unset(char **argv, t_env **env);
int			export(char **argv, t_env **env);
int			env(char **argv, t_env **env);
int			ft_exit(char **argv, t_env **env);

t_builtin	*init_builtins(void);
t_builtin	*find_builtin(char *cmd);

// env utils
t_env		*new_env_node(char *name, char *value, bool is_exported);
t_env 		*env_find_var(t_env *env, char *var);
t_env 		*dup_env(char **env);
void		env_add_last(t_env *node, t_env **env);

int			init_minishell(char **env, t_data *data);
int			execute(t_ast_node *node, t_data *data);
#endif // !EXECUTION_H
