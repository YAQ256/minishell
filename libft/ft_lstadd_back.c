/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyacoub- <cyacoub-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 14:42:25 by cyacoub-          #+#    #+#             */
/*   Updated: 2023/06/20 15:05:58 by cyacoub-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_lst **lst, t_lst *new)
{
	t_lst	*aux;

	if (*lst && new)
	{
		aux = lst[0];
		while (aux->next)
			aux = aux->next;
		aux->next = new;
	}
	else if (new)
		*lst = new;
}
