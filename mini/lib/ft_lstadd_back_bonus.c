/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoguei <monoguei@student.lausanne42.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 15:57:29 by afloras           #+#    #+#             */
/*   Updated: 2025/04/04 11:03:24 by monoguei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new1)
{
	t_list	*lst_last;

	if (!new1)
		return ;
	lst_last = ft_lstlast(*lst);
	if (!lst_last)
		*lst = new1;
	else
		lst_last->next = new1;
}
