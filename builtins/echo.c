/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyacoub- <cyacoub-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 16:20:16 by cyacoub-          #+#    #+#             */
/*   Updated: 2023/09/04 15:32:37 by cyacoub-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	handle_options(char **args, bool *n_option)
{
	size_t	i;
	size_t	j;

	*n_option = false;
	i = 1;
	while (args && args[i])
	{
		if (args[i][0] != '-')
			break ;
		j = 1;
		while (args[i][j])
		{
			if (args[i][j] != 'n')
			{
				if (i == 1)
					*n_option = false;
				return (i - 1);
			}
			*n_option = true;
			j++;
		}
		i++;
	}
	return (i - 1);
}

int	builtin_echo(t_cmd *cmd, t_env **envs)
{
	bool	n_option;
	size_t	i;

	(void)envs;
	i = 1 + handle_options(cmd->cmd, &n_option);
	while (cmd && cmd->cmd && cmd->cmd[i])
	{
		if (cmd->cmd[i][0])
		{
			if (!ft_putstr_fd(cmd->cmd[i], STDOUT_FILENO))
				return (error_write("echo"), EXIT_FAILURE);
			if (cmd->cmd[i + 1])
				if (!ft_putstr_fd(" ", STDOUT_FILENO))
					return (error_write("echo"), EXIT_FAILURE);
		}
		i++;
	}
	if (!n_option)
		if (!ft_putstr_fd("\n", STDOUT_FILENO))
			return (error_write("echo"), EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
