/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstpush.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihajji <ihajji@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 10:23:09 by ihajji            #+#    #+#             */
/*   Updated: 2025/03/19 10:23:09 by ihajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstpush(t_list **from, t_list **to)
{
	t_list	*node;
	t_list	*next;

	if (from == NULL || to == NULL || from == to || ft_lstsize(*from) == 0)
		return ;
	node = *from;
	next = (*from)->next;
	ft_lstadd_front(to, node);
	*from = next;
}
