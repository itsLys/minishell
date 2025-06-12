/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihajji <ihajji@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 20:21:39 by ihajji            #+#    #+#             */
/*   Updated: 2025/06/12 02:48:10 by ihajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef	 EXECUTION_H
# define EXECUTION_H

# include "minishell.h"
# include "parsing.h"

// extern t_data g_data;
int	execute(t_ast_node *node);

t_builtin	*init_builtins(void);
int	find_builtin(char *cmd);

// builtins
int	echo(char **argv);
int	cd(char **argv);
int	pwd(char **argv);
int	unset(char **argv);
int	export(char **argv);
int	env(char **argv);
int	ft_exit(char **argv);

// env utils
char *fetch_env(t_env *env, char *var);

#endif // !EXECUTION_H
