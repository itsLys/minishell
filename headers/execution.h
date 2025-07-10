/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihajji <ihajji@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 20:21:39 by ihajji            #+#    #+#             */
/*   Updated: 2025/07/02 18:39:56 by ihajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include "minishell.h"
# include "parsing.h"

# define PIPE_RD 0
# define PIPE_WR 1
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
	t_ast_node		*ast;
	t_token			*tokens;
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
void				*free_env(t_env *env_copy);

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

// env action
t_env				*new_env_node(char *name, char *value, bool is_exported);
t_env				*env_find_var(t_env *env, char *var);
void				env_add_last(t_env *node, t_env **env);
void				env_remove_node(t_env *node, t_env **env);

// env_utils
void				free_env_node(t_env *node);
t_env				*dup_env(char **env);
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

// expantion utils
void				remove_quote(t_str *input);
void				expand(t_str *input, t_str *mask, t_env *env);
void				expand_var(t_str *input, t_env *env, t_str *mask);
t_str				build_mask(t_str *input);
t_str				get_env_value(t_env *env, char *name);
t_str				get_var_name(t_str *input, t_str *mask, char save_flag);
t_str				get_varname(t_str *input);
bool				is_shell_variable(t_str str);
bool				is_valid_first_char(char c);
bool				is_valid_var_char(char c);
bool				is_shell_variable(t_str str);
t_str_arr			split_input(t_str *input, t_str *mask);
char				**extract_args(t_str_arr *args, t_env *env_list);
bool				contains_wildcard(const char *str);
bool				match_wildcard_from(t_str *pattern, t_str *mask, const char *str, size_t p_index);
bool				match_wildcard(t_str *pattern, t_str *mask, const char *str);
void				expand_all_wildcards(t_str_arr *args, t_str_arr *masks);
void				expand_wildcard_in_str(t_str *input, t_str *mask);
void				expand_wildcard_at(t_str_arr *args,
						t_str_arr *masks, size_t index);
void				expand_heredoc(t_str *filename, t_env *env);
char				*expand_filename(t_str *filename, t_env *env);
void 				remove_contextual_quotes(t_str *str, t_str *mask);

// redirections
int					setup_redir(t_ast_node *redir, int stdio[2], t_data *data);
int					save_stdio(int stdio[2], t_data *data);
void				restore_stdio(int stdio[2]);

// free and exit
void				clean_exit(unsigned int status, t_data *data);
void				free_data(t_data *data);
void				clean_exit(unsigned int status, t_data *data);

// debuging
void    print_ast_type(t_ast_node *node);
#endif // !EXECUTION_H
