/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_snprintf_utils.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbengued <zbengued@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 23:45:59 by zbengued          #+#    #+#             */
/*   Updated: 2025/07/08 00:11:24 by zbengued         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SNPRINTF_UTILS_H

# define FT_SNPRINTF_UTILS_H
# include "libft.h"
# include <stdarg.h>
# define FLAGS "#0-+ "
# define CONVERSIONS "cspdiuxX%"

typedef struct s_buffer
{
	char	*buf;
	size_t	size;
	int		pos;
}	t_buffer;

typedef struct s_flags
{
	int	alt_form;
	int	zero_padded;
	int	left_adjusted;
	int	space_flag;
	int	force_sign;
	int	precision_value;
	int	precision_flag;
	int	width;
	int	coversion;
	int	printed;
	int	total;
}		t_flags;

int		ft_snprintf(char *str, size_t size, const char *fmt, ...);
void	sn_parse_flags(const char *fmt, t_flags *f);
int		sn_parse_integer(const char *fmt, int *n, t_flags *f);
void	sn_print_conversion(char c, va_list args, t_flags *f, t_buffer *buf);
void	sn_parse_fmt(const char *fmt, va_list args, t_flags *f, t_buffer *buf);
int		sn_handle_char(t_flags *f, int c, t_buffer *buf);
int		sn_handle_hex(unsigned int x, t_flags *f, char c, t_buffer *buf);
int		sn_handle_nbr(int n, t_flags *f, t_buffer *buf);
int		sn_handle_ptr(unsigned long long addr, t_flags *f, t_buffer *buf);
int		sn_handle_str(char *str, t_flags *f, t_buffer *buf);
int		sn_handle_unsigned(unsigned int u, t_flags *f, t_buffer *buf);
int		sn_print_width_buf(t_flags *f, int n, t_buffer *buf);
int		sn_get_num_len(unsigned long long n, unsigned int base);
int		sn_check_valid(const char *fmt);
int		sn_catch_err(int n);
int		sn_print_buffer(char c, t_buffer *buf);
#endif // !FT_PRINTF_UTILS_H
