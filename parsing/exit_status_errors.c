/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_status_errors.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyacoub- <cyacoub-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 13:52:29 by cyacoub-          #+#    #+#             */
/*   Updated: 2023/09/04 16:26:58 by cyacoub-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_exit_status(t_cmd *cmd)
{
	char	*mini_join;

	mini_join = ft_strjoin("minishell:", cmd->name_cmd);
	if (g_minishell.exit_status == 2)
	{
		perror(mini_join);
		return (1);
	}
	else if (g_minishell.exit_status == 127)
	{
		error(cmd->name_cmd, "command not found");
		return (1);
	}
	else if (g_minishell.exit_status == 258)
	{
		error("syntax error near unexpected token `newline'", 0);
		return (1);
	}
	free (mini_join);
	return (0);
}
