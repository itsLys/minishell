/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbengued <zbengued@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 22:30:19 by zbengued          #+#    #+#             */
/*   Updated: 2025/06/01 08:12:47 by ihajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <readline/history.h>
# include <readline/readline.h>
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

typedef struct t_builtin
{
	char	*name;
	int		(*function)(void);
} t_builtin ;

typedef struct s_data
{
	char	**env;
	char	*input;
	int		status;
	t_builtin	*builtins;
	
}	t_data;

#endif // !MINISHELL_H
