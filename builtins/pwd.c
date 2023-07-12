/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyacoub- <cyacoub-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 11:13:47 by cyacoub-          #+#    #+#             */
/*   Updated: 2023/07/10 11:14:05 by cyacoub-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	builtin_pwd(t_cmd *cmd, t_env **envs)
{
	char	path[1024];

	(void)envs;
	(void)cmd;
	if (!getcwd(path, 1024))
	{
		perror("pwd");
		return (EXIT_FAILURE);
	}
	if (!ft_putendl_fd(path, STDOUT_FILENO))
		return (error_write("pwd"), EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
