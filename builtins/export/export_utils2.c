/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyacoub- <cyacoub-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 07:06:41 by cyacoub-          #+#    #+#             */
/*   Updated: 2023/09/04 16:23:49 by cyacoub-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_env	*sort_env_list(t_env **env)
{
	t_env	*tmp1;
	t_env	*tmp2;
	int		swapped;

	if (!env)
		return (NULL);
	swapped = 1;
	while (swapped)
	{
		swapped = 0;
		tmp1 = *env;
		while (tmp1->next != NULL)
		{
			tmp2 = tmp1->next;
			if (cmp_env_nodes(tmp1, tmp2))
			{
				swap_env_nodes(tmp1, tmp2);
				swapped = 1;
			}
			tmp1 = tmp1->next;
		}
	}
	return (*env);
}

int	cmp_env_nodes(t_env *tmp1, t_env *tmp2)
{
	size_t	max_length;

	if (ft_strlen(tmp1->key) > ft_strlen(tmp2->key))
		max_length = ft_strlen(tmp1->key);
	else
		max_length = ft_strlen(tmp2->key);
	if (ft_strncmp(tmp1->key, tmp2->key, max_length) > 0)
		return (1);
	else
		return (0);
}

void	swap_env_nodes(t_env *tmp1, t_env *tmp2)
{
	char	*tmp_key;
	char	*tmp_value;

	tmp_key = tmp1->key;
	tmp_value = tmp1->value;
	tmp1->key = tmp2->key;
	tmp1->value = tmp2->value;
	tmp2->key = tmp_key;
	tmp2->value = tmp_value;
}

t_env	*create_new_env_node(char *key_value)
{
	t_env	*new_node;
	char	*equal_sign;

	new_node = (t_env *)malloc(sizeof(t_env));
	if (!new_node)
		return (NULL);
	equal_sign = ft_strchr(key_value, '=');
	if (equal_sign)
	{
		*equal_sign = '\0';
		new_node->key = ft_strdup(key_value);
		new_node->value = ft_strdup(equal_sign + 1);
		*equal_sign = '=';
	}
	else
	{
		new_node->key = ft_strdup(key_value);
		new_node->value = ft_strdup("");
	}
	new_node->next = NULL;
	return (new_node);
}
