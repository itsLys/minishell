/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_char.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihajji <ihajji@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 14:21:09 by ihajji            #+#    #+#             */
/*   Updated: 2024/11/30 09:31:20 by ihajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	handle_char(t_flags *f, int c)
{
	int	count;

	count = 0;
	if (!f->left_adjusted)
		count += print_width(f, 1);
	count += print(c);
	if (f->left_adjusted)
		count += print_width(f, 1);
	return (count);
}
