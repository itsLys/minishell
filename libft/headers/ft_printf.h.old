/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihajji <ihajji@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 08:02:07 by ihajji            #+#    #+#             */
/*   Updated: 2024/11/30 08:07:36 by ihajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H

# define FT_PRINTF_H
# include "libft.h"
# include <stdarg.h>
# define FLAGS "#0-+ "
# define CONVERSIONS "cspdiuxX%"

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

int		handle_char(t_flags *f, int c);
int		handle_str(char *str, t_flags *f);
int		handle_ptr(unsigned long long addr, t_flags *f);
int		handle_nbr(int n, t_flags *f);
int		handle_hex(unsigned int x, t_flags *f, char c);
int		handle_unsigned(unsigned int u, t_flags *f);
int		check_valid(const char *fmt);
int		print_width(t_flags *f, int n);
int		get_num_len(unsigned long long n, unsigned int base);
int		print(char c);
int		catch_err(int n);
int		parse_integer(const char *fmt, int *n, t_flags *f);
void	parse_flags(const char *fmt, t_flags *f);
void	print_conversion(char c, va_list args, t_flags *f);
void	parse_fmt(const char *fmt, va_list args, t_flags *f);
#endif // !FT_PRINTF_H
