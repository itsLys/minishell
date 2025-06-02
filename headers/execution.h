/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihajji <ihajji@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 20:21:39 by ihajji            #+#    #+#             */
/*   Updated: 2025/06/01 08:11:02 by ihajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef	 EXECUTION_H
# define EXECUTION_H

# include "minishell.h"
# include "parsing.h"

void	execute(t_ast_node *node);

#endif // !EXECUTION_H
