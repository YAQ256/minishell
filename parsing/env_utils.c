/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyacoub- <cyacoub-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 14:32:42 by cyacoub-          #+#    #+#             */
/*   Updated: 2023/07/10 14:32:59 by cyacoub-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static size_t	count_envs(t_env *envs)
{
	size_t	i;
	t_env	*tmp;

	i = 0;
	tmp = envs;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	return (i);
}

char	**format_env(t_env *envs)
{
	size_t	i;
	t_env	*tmp;
	char	*key;
	char	**output;

	i = count_envs(envs);
	output = malloc(sizeof(char *) * (i + 1));
	if (!output)
		return (NULL);
	i = 0;
	tmp = envs;
	while (tmp)
	{
		key = ft_strjoin(tmp->key, "=");
		output[i] = ft_strjoin(key, tmp->value);
		free(key);
		i++;
		tmp = tmp->next;
	}
	output[i] = NULL;
	return (output);
}
