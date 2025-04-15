/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstswap.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihajji <ihajji@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 10:23:00 by ihajji            #+#    #+#             */
/*   Updated: 2025/03/19 10:23:09 by ihajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstswap(t_list **head)
{
	void	*tmp;
	t_list	*node;
	t_list	*next;

	if (ft_lstsize(*head) <= 1)
		return ;
	node = *head;
	next = (*head)->next;
	tmp = node->content;
	node->content = next->content;
	next->content = tmp;
}
