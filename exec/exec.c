/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyacoub- <cyacoub-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 14:47:36 by saazcon-          #+#    #+#             */
/*   Updated: 2023/09/05 20:42:11 by cyacoub-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_check_path(t_cmd *ps, char **envp)
{
	int		i;
	char	**env_path;
	char	*path;
	char	*path_cmd;

	i = ft_path(envp);
	env_path = ft_split(envp[i] + 5, ':');
	i = -1;
	while (env_path[++i])
	{
		path = ft_strjoin(env_path[i], "/");
		path_cmd = ft_strjoin(path, ps->cmd[0]);
		free(path);
		if (access(path_cmd, X_OK) == 0)
		{
			ps->pth_cmd = ft_strdup(path_cmd);
			free(path_cmd);
			ft_free_double(env_path);
			g_minishell.exit_status = 0;
			return ;
		}
		free(path_cmd);
	}
	ft_free_double(env_path);
	g_minishell.exit_status = 127;
}

void	ft_execute(t_cmd *ps, char **envp, int infile, int outfile)
{
	pid_t	pid;

	pid = ft_fork();
	if (pid == 0)
	{
		sig_child();
		ft_infile(ps, infile);
		ft_outfile(ps, outfile);
		if (execve(ps->pth_cmd, ps->cmd, envp) == -1)
			exit(1);
	}
}

int	ft_pipex(t_cmd *cmd, char **envp, int inhe)
{
	int	pipex[2];

	ft_pipe(pipex);
	ft_execute(cmd, envp, inhe, pipex[WRITE]);
	close(pipex[WRITE]);
	if (inhe != STDIN_FILENO)
		close(inhe);
	return (pipex[READ]);
}

void	ft_exec_data(t_env **env, t_cmd *ps, char **envp, int *len)
{
	g_minishell.exit_status = 0;
	ft_init_break(ps, envp);
	ft_init_heredoc(ps, env);
	*len = ft_lstlen(ps);
}

void	ft_init_exec(t_cmd **cmds, t_env **env)
{
	char	**envp;
	int		file;
	int		len;
	t_cmd	*ps;

	ps = *cmds;
	envp = format_env(*env);
	ft_exec_data(env, ps, envp, &len);
	if (g_minishell.exit_status != 0 && check_exit_status(ps))
		return ;
	file = STDIN_FILENO;
	while (ps)
	{
		if (is_builtin(ps))
			file = ft_builtin(ps, env, len);
		else if (!ps->next)
			ft_execute(ps, envp, file, STDOUT_FILENO);
		else
			file = ft_pipex(ps, envp, file);
		ps = ps->next;
	}
	if (file != STDIN_FILENO)
		close(file);
	ft_wait_for_childs();
	ft_free_cmd(cmds, envp);
}
