/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstrotate.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihajji <ihajji@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 10:23:09 by ihajji            #+#    #+#             */
/*   Updated: 2025/03/19 10:23:09 by ihajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstrotate(t_list **head)
{
	t_list	*first;

	if (head == NULL || ft_lstsize(*head) <= 1)
		return ;
	first = *head;
	*head = (*head)->next;
	ft_lstlast(*head)->next = first;
	first->next = NULL;
}
