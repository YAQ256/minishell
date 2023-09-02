/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saazcon- <saazcon-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 11:19:44 by cyacoub-          #+#    #+#             */
/*   Updated: 2023/09/02 08:33:47 by saazcon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_env	*get_env(t_env *envs, char *key)
{
	t_env	*tmp;

	if (!key)
		return (NULL);
	tmp = envs;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, key) == 0)
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}

static t_env	*new_env(char *key, char *value)
{
	t_env	*new;

	if (!key || !value)
		return (NULL);
	new = malloc(sizeof(t_env));
	if (!new)
		return (NULL);
	new->key = ft_strdup(key);
	new->value = value;
	new->next = NULL;
	return (new);
}

t_env	*set_env(t_env **envs, char *key, char *value)
{
	t_env	*new;
	t_env	*last;

	new = get_env(*envs, key);
	if (new)
	{
		free(new->value);
		new->value = value;
		return (new);
	}
	new = new_env(key, value);
	if (!new)
		return (NULL);
	if (*envs)
	{
		last = *envs;
		while (last->next)
			last = last->next;
		last->next = new;
	}
	else
		*envs = new;
	return (new);
}

t_env	*remove_env(t_env **envs, char *key)
{
	t_env	*current;
	t_env	*tmp;

	if (!*envs)
		return (NULL);
	if (ft_strcmp((*envs)->key, key) == 0)
	{
		tmp = *envs;
		*envs = (*envs)->next;
		free_env(tmp);
		return (*envs);
	}
	current = *envs;
	while (current->next)
	{
		if (ft_strcmp(current->next->key, key) == 0)
		{
			tmp = current->next;
			current->next = current->next->next;
			free_env(tmp);
			return (*envs);
		}
		current = current->next;
	}
	return (NULL);
}

void	free_env(t_env *env)
{
	if (!env)
		return ;
	if (env->key)
		free(env->key);
	if (env->value)
		free(env->value);
	free(env);
}
