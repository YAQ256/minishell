/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyacoub- <cyacoub-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 14:21:16 by cyacoub-          #+#    #+#             */
/*   Updated: 2023/07/11 14:21:25 by cyacoub-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	s1_len;
	size_t	s2_len;

	if (!s1 || !s2)
		return (-1);
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	return (ft_strncmp(s1, s2, s1_len + s2_len));
}
