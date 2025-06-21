/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihajji <ihajji@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 20:21:39 by ihajji            #+#    #+#             */
/*   Updated: 2025/06/21 11:25:42 by ihajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include "minishell.h"
# include "parsing.h"
# define PIPE_RD 0
# define PIPE_WR 1

typedef enum e_mode
{
	CONCAT,
	ASSIGN,
	EXPORT
}					t_mode;

typedef struct s_env
{
	char			*name;
	char			*value;
	bool			exported;
	struct s_env	*next;
}					t_env;

typedef struct s_data
{
	t_env			*env;
	char			*input;
	int				status;
	char			*oldpwd;
	char			*pwd;
}					t_data;

typedef struct t_builtin
{
	char			*name;
	int				(*function)(char **argv, t_env **env, t_data *data);
}					t_builtin;
//testing function
void				print_env(t_env *env);

t_data				*g_data(void);

// memory
void				*free_env_copy(t_env *env_copy);

// init
int					init_minishell(char **env, t_data *data);

// builtins
int					echo(char **argv, t_env **env, t_data *data);
int					cd(char **argv, t_env **env, t_data *data);
int					pwd(char **argv, t_env **env, t_data *data);
int					unset(char **argv, t_env **env, t_data *data);
int					export(char **argv, t_env **env, t_data *data);
int					env(char **argv, t_env **env, t_data *data);
int					ft_exit(char **argv, t_env **env, t_data *data);

// builtins utils
t_builtin			*init_builtins(void);
t_builtin			*find_builtin(char *cmd);

// env utils
t_env				*new_env_node(char *name, char *value, bool is_exported);
t_env				*env_find_var(t_env *env, char *var);
t_env				*dup_env(char **env);
void				env_add_last(t_env *node, t_env **env);
void				sort_env(t_env **env);

// make env
char				**make_envp(t_env *env);

// export utils
bool				is_valid(char *arg, t_mode *mode);
void				export_var(char *arg, t_env **env);
void				concat_var(char *arg, t_env **env);
void				assign_var(char *arg, t_env **env);
t_env				*dup_env_sorted(t_env *env);

// shell utils
int					print_error(char *name, char *msg);

// execution
int					execute(t_ast_node *node, t_data *data, bool run_in_shell);
int					execute_pipeline(t_ast_node *node, t_data *data);
int					execute_compound(t_ast_node *node, t_data *data);
int					execute_simple_command(t_ast_node *node, t_data *data, bool run_in_shell);
int					execute_subshell(t_ast_node *node, t_data *data);
#endif // !EXECUTION_H
