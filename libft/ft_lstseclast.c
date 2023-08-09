/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstseclast.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyacoub- <cyacoub-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 17:03:28 by amtadevo          #+#    #+#             */
/*   Updated: 2023/06/20 15:06:05 by cyacoub-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_lst	*ft_lstseclast(t_lst *lst)
{
	t_lst	*sec_last;

	if (lst == NULL)
		return (lst);
	while (lst->next != NULL)
	{
		sec_last = lst;
		lst = lst->next;
	}
	return (sec_last);
}
