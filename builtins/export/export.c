/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyacoub- <cyacoub-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 15:48:15 by cyacoub-          #+#    #+#             */
/*   Updated: 2023/08/17 11:49:48 by cyacoub-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	builtin_export(t_cmd *cmds, t_env **env)
{
	int		i;
	t_env	*sorted_env;
	char	**word;

	word = cmds->args;
	i = 1;
	if (cmds->args[1] == NULL)
	{
		sorted_env = sort_env_list(env);
		print_env_list(&sorted_env);
		return (EXIT_SUCCESS);
	}
	while (word[i])
	{
		if (!process_argument(word[i], env))
			return (g_minishell.exit_status);
		i++;
	}
	return (EXIT_SUCCESS);
}

void	print_env_list(t_env **env)
{
	t_env	*tmp;

	tmp = *env;
	while (tmp)
	{
		ft_putstr_fd("declare -x ", 1);
		ft_putstr_fd(tmp->key, 1);
		if (tmp->value && tmp->value[0] != '\0')
		{
			ft_putstr_fd("=\"", 1);
			ft_putstr_fd(tmp->value, 1);
			ft_putendl_fd("\"", 1);
		}
		else
		{
			ft_putendl_fd("", 1);
		}
		tmp = tmp->next;
	}
}

int	process_argument(char *arg, t_env **envs)
{
	char	*equal_sign;

	equal_sign = ft_strchr(arg, '=');
	if (is_valid_identifier(arg))
	{
		if (equal_sign != NULL)
			handle_argument_with_equals(arg, envs);
		else
			handle_argument_without_equals(arg, envs);
		return (1);
	}
	else
	{
		ft_putstr_fd("minishell: export: `", 2);
		ft_putstr_fd(arg, 2);
		ft_putendl_fd("': not a valid identifier", 2);
		g_minishell.exit_status = 1;
		return (0);
	}
}

int	is_valid_identifier(char *arg)
{
	int	i;

	i = 0;
	if (arg[i] == '_' || ft_isalpha(arg[i]))
	{
		i++;
		while (arg[i] != '\0' && arg[i] != '=')
		{
			if (!(ft_isalnum(arg[i]) || arg[i] == '_'))
				return (0);
			i++;
		}
		return (1);
	}
	return (0);
}
