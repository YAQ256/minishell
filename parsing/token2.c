/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyacoub- <cyacoub-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 14:10:00 by cyacoub-          #+#    #+#             */
/*   Updated: 2023/07/11 14:10:10 by cyacoub-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool	special_char(char c)
{
	return (!((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')
			|| (c >= '0' && c <= '9') || (c == '_')));
}

char	**token_split(char **tokens, size_t *i, bool *split_token, int k)
{
	char	**new_tokens;
	size_t	j;

	new_tokens = (char **)malloc(sizeof(char *) * (k + 2));
	if (!new_tokens)
		return (0);
	j = 0;
	while (j < (*i) - 1)
	{
		new_tokens[j] = tokens[j];
		j++;
	}
	k = 0;
	while (!is_space(tokens[(*i) - 1][k]))
		k++;
	new_tokens[j++] = ft_substr(tokens[(*i) - 1], 0, k);
	new_tokens[j] = ft_strdup(tokens[(*i) - 1] + k + 1);
	free(tokens[(*i) - 1]);
	free(tokens);
	(*i)++;
	*split_token = false;
	return (new_tokens);
}

int	check_end_by_quote(char *line, int i)
{
	i--;
	while (i > 0 && is_space(line[i]))
		i--;
	if (line[i] == '"' || line[i] == '\'')
		return (1);
	return (0);
}

int	isinquote(char *token, size_t *i)
{
	size_t	j;

	j = 0;
	while (j < (*i))
	{
		if (token[j] == '"')
		{
			handle_quotes(token, &j);
			if (j > (*i))
				return (1);
		}
		j++;
	}
	return (0);
}
