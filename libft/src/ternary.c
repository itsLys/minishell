/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ternary.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbengued <zbengued@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 22:14:41 by zbengued          #+#    #+#             */
/*   Updated: 2025/06/23 23:17:21 by zbengued         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

// NOTE : How to use expamle : tmp_value(&(int){1}) => passing 1 
void	*tmp(void *value, size_t size)
{
	static unsigned char	buffers[N_TMP][TMP_SIZE];
	static size_t			i;
	void					*slot;

	if (!value || size == 0 || size > sizeof(buffers[0]))
		return (NULL);
	slot = buffers[i];
	ft_memcpy(slot, value, size);
	i = (i + 1) % N_TMP;
	return (slot);
}

// NOTE : How to use expamle :
// ternary((t_ternary){.condition(1 > 5),
//					   .if_true = tmp_(&(int){1}, 4),
//					   .if_false = tmp_(&(int){5}, 4),
//					   .size = 4, 
//					   .dest = &i});
	// ternary((t_ternary){(1 > 5), 1, 2, sizeof(int), &i})
void	ternary_(t_ternary t)
{
	if (!t.if_true || !t.if_false || !t.dest || t.size == 0)
		return ;
	if (t.condition)
		ft_memcpy(t.dest, t.if_true, t.size);
	else
		ft_memcpy(t.dest, t.if_false, t.size);
}

void	*ternary(int condition, void *a, void *b)
{
    if (condition)
        return (a);
    else
        return (b);
}
