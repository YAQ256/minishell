/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saazcon- <saazcon-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 14:33:16 by cyacoub-          #+#    #+#             */
/*   Updated: 2023/09/02 10:04:47 by saazcon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	error(char *msg, char *more)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(msg, STDERR_FILENO);
	if (more)
	{
		ft_putstr_fd(": ", STDERR_FILENO);
		ft_putstr_fd(more, STDERR_FILENO);
	}
	ft_putchar_fd('\n', STDERR_FILENO);
}

void	error_st(char *msg, char *more, int exit_status)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(msg, STDERR_FILENO);
	if (more)
	{
		ft_putstr_fd(": ", STDERR_FILENO);
		ft_putstr_fd(more, STDERR_FILENO);
	}
	ft_putchar_fd('\n', STDERR_FILENO);
	g_minishell.exit_status = exit_status;
}

void	error_e(char *msg, char *more, int exit_status)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(msg, STDERR_FILENO);
	if (more)
	{
		ft_putstr_fd(": ", STDERR_FILENO);
		ft_putstr_fd(more, STDERR_FILENO);
	}
	ft_putchar_fd('\n', STDERR_FILENO);
	g_minishell.exit_status = exit_status;
	exit (exit_status);
}

void	error_numerical_arg(char *name, char *arg)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(name, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putstr_fd(arg, STDERR_FILENO);
	ft_putstr_fd(": numeric argument required\n", STDERR_FILENO);
}

void	error_write(char *cmd)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(cmd, STDERR_FILENO);
	ft_putstr_fd(": write error: ", STDERR_FILENO);
	ft_putstr_fd("No space left on device\n", STDERR_FILENO);
}
