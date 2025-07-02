/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbengued <zbengued@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 15:06:33 by zbengued          #+#    #+#             */
/*   Updated: 2025/07/01 16:27:59 by zbengued         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signals.h>

int	g_interrupted[2] = {0};

static void	sigint_handler_prompt(int sig)
{
	(void)sig;
	if (!g_interrupted[1])
	{
		g_interrupted[1] = 1;
		ft_dprintf(STDOUT_FILENO, "\n");
	}
}
static int	my_rl_event_hook()
{
	if (g_interrupted[1])
		rl_done = 1;
	return (0);
}

void	setup_signals(void)
{
	g_interrupted[0] = 0;
	g_interrupted[1] = 0;
	signal(SIGINT, sigint_handler_prompt);
	signal(SIGQUIT, SIG_IGN);
	rl_event_hook = my_rl_event_hook;
}
