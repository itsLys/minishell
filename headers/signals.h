/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbengued <zbengued@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 15:09:13 by zbengued          #+#    #+#             */
/*   Updated: 2025/07/01 16:28:13 by zbengued         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNALS_H
# define SIGNALS_H

# define EXIT_STATUS 2
# define SIGNAL_INTERRUPT 1
# define HEREDOC_INTERRUPT 0

extern int	g_interrupted[3];

void	setup_signals(void);

#endif // !SIGNALS_H
