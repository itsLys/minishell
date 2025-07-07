/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_char.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbengued <zbengued@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 23:46:14 by zbengued          #+#    #+#             */
/*   Updated: 2025/07/07 23:46:15 by zbengued         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_snprintf_utils.h"

int	sn_handle_char(t_flags *f, int c, t_buffer *buf)
{
	int	count;

	count = 0;
	if (!f->left_adjusted)
		count += sn_print_width_buf(f, 1, buf);
	count += sn_print_buffer(c, buf);
	if (f->left_adjusted)
		count += sn_print_width_buf(f, 1, buf);
	return (count);
}
