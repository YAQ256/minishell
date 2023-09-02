/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saazcon- <saazcon-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 16:21:44 by cyacoub-          #+#    #+#             */
/*   Updated: 2023/09/02 08:31:46 by saazcon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	error_numerical_arg(char *arg)
{
	ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
	ft_putstr_fd(arg, STDERR_FILENO);
	ft_putstr_fd(": numeric argument required\n", STDERR_FILENO);
}

static int	verify_args(char **args)
{
	int	i;
	int	j;

	i = 1;
	while (args[i])
	{
		j = 0;
		if (args[i][0] == '-' || args[i][0] == '+')
			j++;
		while (args[i][j])
		{
			if (!ft_isdigit(args[i][j]))
				return (error_numerical_arg(args[i]), 255);
			j++;
		}
		if (args[i + 1])
		{
			g_minishell.force_exit = false;
			return (error("exit", "too many arguments"), EXIT_FAILURE);
		}
		i++;
	}
	return (EXIT_SUCCESS);
}

static bool	is_overflowing(const char *s)
{
	bool	is_negative;

	is_negative = false;
	if (s && *s == '-')
		is_negative = true;
	if (ft_strlen(s) - is_negative > 19)
		return (true);
	if (is_negative && ft_strcmp(s + 1, "9223372036854775808") > 0)
		return (true);
	else if (!is_negative && ft_strcmp(s, "9223372036854775807") > 0)
		return (true);
	return (false);
}

void	exit_arg(t_cmd *cmd)
{
	long long	exit_code;
	t_env		*tmp;

	exit_code = ft_atoll(cmd->args[1]);
	free_cmds(cmd);
	while (g_minishell.envs)
	{
		tmp = g_minishell.envs;
		g_minishell.envs = g_minishell.envs->next;
		free_env(tmp);
	}
	exit(exit_code);
}

int	builtin_exit(t_cmd *cmd, t_env **envs)
{
	int		verify_status;

	(void)envs;
	g_minishell.force_exit = true;
	if (!cmd->has_pipe)
		ft_putstr_fd("exit\n", STDERR_FILENO);
	verify_status = verify_args(cmd->args);
	if (verify_status != EXIT_SUCCESS)
		return (verify_status);
	if (cmd->args[1] && is_overflowing(cmd->args[1]))
		return (error_numerical_arg(cmd->args[1]), 255);
	if (cmd->args[1])
		exit_arg(cmd);
	return (EXIT_SUCCESS);
}
