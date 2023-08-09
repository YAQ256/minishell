/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyacoub- <cyacoub-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 14:44:10 by cyacoub-          #+#    #+#             */
/*   Updated: 2023/06/20 15:06:01 by cyacoub-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstiter(t_lst *lst, void *(*f)(char*))
{
	t_lst	*tmp;

	tmp = lst;
	while (tmp)
	{
		f(tmp->data);
		tmp = tmp -> next;
	}
}
