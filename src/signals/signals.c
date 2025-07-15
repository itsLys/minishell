/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbengued <zbengued@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 15:06:33 by zbengued          #+#    #+#             */
/*   Updated: 2025/07/14 14:38:45 by ihajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signals.h>
#include <minishell.h>

int	g_interrupted[3] = {0};

static void	sigint_handler_prompt(int sig)
{
	(void)sig;
	if (!g_interrupted[1])
	{
		g_interrupted[1] = 1;
		g_interrupted[2] = 130;
	}
}

static int	my_rl_event_hook(void)
{
	if (g_interrupted[1])
	{
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
		rl_done = 1;
	}
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
