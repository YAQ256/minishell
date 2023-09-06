/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saazcon- <saazcon-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 13:22:19 by cyacoub-          #+#    #+#             */
/*   Updated: 2023/09/06 09:56:18 by saazcon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_echo_env_pwd(t_cmd *cmd, t_env **env)
{
	if (ft_strcmp(cmd->name_cmd, "echo") == 0)
		g_minishell.exit_status = builtin_echo(cmd, env);
	else if (ft_strcmp(cmd->name_cmd, "env") == 0)
		g_minishell.exit_status = builtin_env(cmd, env);
	else if (ft_strcmp(cmd->name_cmd, "pwd") == 0)
		g_minishell.exit_status = builtin_pwd(cmd, env);
}

void	ft_cd_exit_export_unset(t_cmd *cmd, t_env **env)
{
	if (ft_strcmp(cmd->name_cmd, "cd") == 0)
		g_minishell.exit_status = builtin_cd(cmd, env);
	else if (ft_strcmp(cmd->name_cmd, "exit") == 0)
		g_minishell.exit_status = builtin_exit(cmd, env);
	else if (ft_strcmp(cmd->name_cmd, "export") == 0)
		g_minishell.exit_status = builtin_export(cmd, env);
	else if (ft_strcmp(cmd->name_cmd, "unset") == 0)
		g_minishell.exit_status = builtin_unset(cmd, env);
}

int	ft_execute_built(t_cmd *cmd, t_env **env)
{
	int	pipex[2];

	ft_pipe(pipex);
	if (!ft_fork())
	{
		close(pipex[READ]);
		if (cmd->outfile)
			ft_outfile(cmd, STDOUT_FILENO);
		else
			dup2(pipex[WRITE], STDOUT_FILENO);
		close(pipex[WRITE]);
		ft_echo_env_pwd(cmd, env);
		exit(0);
	}
	close(pipex[WRITE]);
	return (pipex[READ]);
}

int	ft_builtin(t_cmd *cmd, t_env **env, int len)
{
	if (ft_strcmp(cmd->name_cmd, "echo") == 0 || \
		ft_strcmp(cmd->name_cmd, "env") == 0 || \
		ft_strcmp(cmd->name_cmd, "pwd") == 0)
	{
		if ((len == 1 || !cmd->next) && (cmd->outfile == NULL))
			ft_echo_env_pwd(cmd, env);
		else
			return (ft_execute_built(cmd, env));
	}
	else if (len == 1)
		ft_cd_exit_export_unset(cmd, env);
	return (STDIN_FILENO);
}

int	is_builtin(t_cmd *cmd)
{
	if (cmd->name_cmd == NULL)
		return (0);
	else if (ft_strcmp(cmd->name_cmd, "cd") == 0)
		return (1);
	else if (ft_strcmp(cmd->name_cmd, "echo") == 0)
		return (1);
	else if (ft_strcmp(cmd->name_cmd, "env") == 0)
		return (1);
	else if (ft_strcmp(cmd->name_cmd, "exit") == 0)
		return (1);
	else if (ft_strcmp(cmd->name_cmd, "export") == 0)
		return (1);
	else if (ft_strcmp(cmd->name_cmd, "pwd") == 0)
		return (1);
	else if (ft_strcmp(cmd->name_cmd, "unset") == 0)
		return (1);
	return (0);
}
