/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyacoub- <cyacoub-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 15:48:15 by cyacoub-          #+#    #+#             */
/*   Updated: 2023/09/04 16:23:36 by cyacoub-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	error_identifier(char *identifier)
{
	ft_putstr_fd("minishell: export: `", STDERR_FILENO);
	ft_putstr_fd(identifier, STDERR_FILENO);
	ft_putstr_fd("': not a valid identifier\n", STDERR_FILENO);
}

int	builtin_export(t_cmd *cmd, t_env **envs)
{
	size_t	i;
	size_t	j;

	i = 1;
	while (cmd->args && cmd->args[i])
	{
		j = 0;
		while (cmd->args[i][j] && cmd->args[i][j] != '=')
		{
			if ((cmd->args[i][0] >= '0' && cmd->args[i][0] <= '9')
				|| special_char(cmd->args[i][j]))
				return (error_identifier(cmd->args[i]), EXIT_FAILURE);
			j++;
		}
		if (j == 0)
			return (error_identifier(&cmd->args[i][j]), EXIT_FAILURE);
		if (cmd->args[i][j])
		{
			cmd->args[i][j] = '\0';
			if (!set_env(envs, cmd->args[i], ft_strdup(&cmd->args[i][j + 1])))
				return (EXIT_FAILURE);
		}
		i++;
	}
	return (EXIT_SUCCESS);
}
