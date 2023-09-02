/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saazcon- <saazcon-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 11:14:38 by cyacoub-          #+#    #+#             */
/*   Updated: 2023/09/02 08:31:55 by saazcon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	builtin_unset(t_cmd *cmd, t_env **envs)
{
	size_t	i;

	i = 1;
	while (cmd->args[i])
	{
		if (!remove_env(envs, cmd->args[i]))
			return (0);
		i++;
	}
	return (EXIT_SUCCESS);
}
