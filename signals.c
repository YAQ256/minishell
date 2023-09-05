/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saazcon- <saazcon-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 14:34:30 by cyacoub-          #+#    #+#             */
/*   Updated: 2023/09/05 18:58:33 by saazcon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	main_signal(int signal)
{
	g_minishell.signal = signal; //para que tu quietes esto??
	if (signal == SIGINT)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		set_env(&g_minishell.envs, "?", ft_itoa(128 + g_minishell.signal));
	}
}

/* void	hd_signal(int signal)
{
	g_minishell.signal = signal;
	if (signal == SIGINT)
	{
		ioctl(0, TIOCSTI, "\n");
		rl_on_new_line();
		set_env(&g_minishell.envs, "?", ft_itoa(128 + g_minishell.signal)); //corregir
	}
} */

void	sig_heredoc(void)
{
	//signal(SIGINT, hd_signal);
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_IGN);
}

void	sig_child(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}

void	sig_parent(void)
{
	signal(SIGINT, main_signal);
	signal(SIGQUIT, SIG_IGN);
}

void	sig_ignore(void)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}

// void	heredoc_signal(int signal)
// {
// 	g_minishell.signal = signal;
// 	g_minishell.heredoc = true;
// 	set_env(&g_minishell.envs, "?",
// 		ft_itoa(128 + g_minishell.signal));
// }

// void	cmd_signal(int signal)
// {
// 	g_minishell.signal = signal;
// 	if (signal == SIGINT)
// 	{
// 		write(1, "\n", 1);
// 		rl_on_new_line();
// 		rl_replace_line("", 0);
// 	}
// 	if (signal == SIGQUIT)
// 	{
// 		ft_putendl_fd("Quit", STDERR_FILENO);
// 	}
// } 
