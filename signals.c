/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyacoub- <cyacoub-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 14:34:30 by cyacoub-          #+#    #+#             */
/*   Updated: 2023/07/10 14:34:47 by cyacoub-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	main_signal(int signal)
{
	g_minishell.signal = signal;
	if (signal == SIGINT)
	{
		if (!g_minishell.heredoc)
			write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		set_env(&g_minishell.envs, "?",
			ft_itoa(128 + g_minishell.signal));
	}
}

void	heredoc_signal(int signal)
{
	g_minishell.signal = signal;
	g_minishell.heredoc = true;
	set_env(&g_minishell.envs, "?",
		ft_itoa(128 + g_minishell.signal));
}

void	cmd_signal(int signal)
{
	g_minishell.signal = signal;
	if (signal == SIGINT)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
	}
	if (signal == SIGQUIT)
	{
		ft_putendl_fd("Quit", STDERR_FILENO);
	}
}
